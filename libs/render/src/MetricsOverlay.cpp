#include "render/MetricsOverlay.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>

#include "core/utils/Profiler.h"
#include "core/utils/Logger.h"
#include "core/objects/Ball.h"

namespace render {

MetricsOverlay::MetricsOverlay(GLFWwindow* window) {
    if (!window) {
        LOG_ERROR("MetricsOverlay initialized with nullptr GLFWwindow handle!");
        return; 
    }

    if (ImGui::GetCurrentContext() != nullptr && ImGui::GetIO().BackendPlatformUserData != nullptr) {
        LOG_WARN("ImGui GLFW backend already initialized! Cleaning up existing backend...");
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    LOG_INFO("Initializing ImGui Metrics Overlay instance...");
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 460");

    m_initialized = true; // Mark as successfully initialized
}

MetricsOverlay::~MetricsOverlay() {
    if (!m_initialized) return;

    LOG_INFO("Destroying ImGui Metrics Overlay instance...");
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void MetricsOverlay::beginFrame() const {
    if (!m_initialized) return;

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

// TODO: Decouple this, probably best to make another gui class for controlling the simulation
// TODO: might be worth making a parent IMGUI class that these classes inherit from, and render these using polymorphism
// TODO: rearchitect the render library to be better basded on this new architecture
void MetricsOverlay::render() const {
    if (!m_initialized || !m_visible) return;

    // --- GUI Docking Lock State ---
    static bool isLocked = true;

    // --- Display Stabilizer (Updates text values every 100ms) ---
    static float displayFps = 0.0f;
    static float displayFrameMs = 0.0f;
    static float display1LowMs = 0.0f;
    static float displayMaxMs = 0.0f;
    static float lastUpdateTime = 0.0f;

    // --- Window Visibility Toggles ---
    static bool showGraph = true;
    static bool showControls = true;

    float currentTime = static_cast<float>(glfwGetTime());
    const auto& profiler = core::util::Profiler::instance();

    if (currentTime - lastUpdateTime >= 0.1f) {
        displayFps = profiler.getFps();
        displayFrameMs = profiler.getFrameTimeMs();
        display1LowMs = profiler.get1PercentLowMs();
        displayMaxMs = profiler.getMaxFrameTimeMs();
        lastUpdateTime = currentTime;
    }

    // Common layout flags
    ImGuiWindowFlags windowFlags = ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings;
    if (isLocked) {
        windowFlags |= ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration;
    }

    // =========================================================================
    // 1. MAIN METRICS WINDOW (TOP-LEFT)
    // =========================================================================
    if (isLocked) {
        ImGui::SetNextWindowPos(ImVec2(10.0f, 10.0f), ImGuiCond_Always);
    } else {
        ImGui::SetNextWindowPos(ImVec2(10.0f, 10.0f), ImGuiCond_FirstUseEver);
    }
    ImGui::SetNextWindowBgAlpha(0.40f);

    float mainOverlayHeight = 0.0f;

    if (ImGui::Begin("Engine Metrics", nullptr, windowFlags)) {
        // --- Title / Header ---
        ImGui::TextColored(ImVec4(0.2f, 0.8f, 1.0f, 1.0f), "PERFORMANCE");
        ImGui::SameLine(ImGui::GetWindowWidth() - 75.0f);
        
        if (ImGui::SmallButton(isLocked ? "Unlock" : " Lock ")) {
            isLocked = !isLocked;
        }

        ImGui::Separator();

        // --- Core Timings & FPS ---
        ImGui::Text("FPS:          %.1f (%.2f ms)", displayFps, displayFrameMs);
        ImGui::Text("1%% Low:       %.2f ms (%.1f FPS)", display1LowMs, display1LowMs > 0.0f ? 1000.0f / display1LowMs : 0.0f);
        ImGui::Text("Max Spike:    %.2f ms (%.1f FPS)", displayMaxMs, displayMaxMs > 0.0f ? 1000.0f / displayMaxMs : 0.0f);
        ImGui::Text("Uptime:       %.2f s", currentTime);

        ImGui::Spacing();

        // --- Stage Breakdown ---
        if (profiler.getPhysicsTimeMs() > 0.0f || profiler.getRenderTimeMs() > 0.0f) {
            ImGui::TextColored(ImVec4(0.9f, 0.5f, 0.2f, 1.0f), "PIPELINE STAGES");
            ImGui::Separator();
            ImGui::Text("Physics Step: %.2f ms", profiler.getPhysicsTimeMs());
            ImGui::Text("Render Step:  %.2f ms", profiler.getRenderTimeMs());
            ImGui::Spacing();
        }

        // --- World State ---
        ImGui::TextColored(ImVec4(0.4f, 0.9f, 0.4f, 1.0f), "WORLD STATE");
        ImGui::Separator();
        ImGui::Text("Total Balls:  %zu", profiler.getEntityCount());
        ImGui::Text("Contacts:     %zu", profiler.getCollisionCount());

        ImGui::Spacing();

        // --- Memory Estimation ---
        ImGui::TextColored(ImVec4(1.0f, 0.8f, 0.3f, 1.0f), "MEMORY");
        ImGui::Separator();
        size_t memoryBytes = profiler.getEntityCount() * sizeof(core::Ball);
        ImGui::Text("Entity Mem:   %.2f KB", static_cast<float>(memoryBytes) / 1024.0f);

        ImGui::Spacing();
        ImGui::Separator();

        ImGui::Checkbox("Show Frametime Graph", &showGraph);
        ImGui::Checkbox("Show Controls Panel", &showControls);

        mainOverlayHeight = ImGui::GetWindowHeight();
    }
    ImGui::End();

    // =========================================================================
    // 2. SEPARATE FRAMETIME GRAPH WINDOW (BELOW METRICS)
    // =========================================================================
    if (showGraph) {
        static float frameTimeBuffer[100] = {};
        static int bufferOffset = 0;

        frameTimeBuffer[bufferOffset] = profiler.getRawFrameTimeMs();
        bufferOffset = (bufferOffset + 1) % 100;

        if (isLocked) {
            ImGui::SetNextWindowPos(ImVec2(10.0f, 10.0f + mainOverlayHeight + 10.0f), ImGuiCond_Always);
        } else {
            ImGui::SetNextWindowPos(ImVec2(10.0f, 10.0f + mainOverlayHeight + 10.0f), ImGuiCond_FirstUseEver);
        }

        ImGui::SetNextWindowBgAlpha(0.40f);

        ImGuiWindowFlags graphFlags = ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings;
        if (isLocked) {
            graphFlags |= ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration;
        }

        if (ImGui::Begin("Frametime Profiler Graph", &showGraph, graphFlags)) {
            ImGui::TextColored(ImVec4(0.2f, 0.8f, 1.0f, 1.0f), "FRAMETIME HISTORY");
            ImGui::Separator();

            ImGui::PlotLines("##frametime", 
                             frameTimeBuffer, 
                             100, 
                             bufferOffset, 
                             "Frametime (ms)", 
                             0.0f, 
                             33.3f, 
                             ImVec2(220.0f, 60.0f));
        }
        ImGui::End();
    }

    // =========================================================================
    // 3. SIMULATION CONTROLS WINDOW (TOP-RIGHT)
    // =========================================================================
    if (showControls) {
        // Anchor to top-right corner with Pivot (1.0f, 0.0f)
        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImVec2 topRightPos = ImVec2(viewport->WorkPos.x + viewport->WorkSize.x - 10.0f, viewport->WorkPos.y + 10.0f);

        if (isLocked) {
            ImGui::SetNextWindowPos(topRightPos, ImGuiCond_Always, ImVec2(1.0f, 0.0f));
        } else {
            ImGui::SetNextWindowPos(topRightPos, ImGuiCond_FirstUseEver, ImVec2(1.0f, 0.0f));
        }

        ImGui::SetNextWindowBgAlpha(0.40f);

        if (ImGui::Begin("Simulation Controls", &showControls, windowFlags)) {
            ImGui::TextColored(ImVec4(0.9f, 0.4f, 0.8f, 1.0f), "SIMULATION CONTROLS");
            ImGui::Separator();

            // --- Pause / Play / Step ---
            static bool paused = false;
            static bool stepRequested = false;

            if (ImGui::Button(paused ? "  Play  " : " Pause ")) {
                paused = !paused;
            }

            ImGui::SameLine();
            if (ImGui::Button("Step Frame")) {
                stepRequested = true;
            }

            ImGui::SameLine();
            if (ImGui::Button("Reset World")) {
                // Signal world reset
            }

            ImGui::Spacing();

            // --- Time Scale Slider ---
            static float timeScale = 1.0f;
            ImGui::SliderFloat("Time Scale", &timeScale, 0.0f, 3.0f, "%.2fx");

            ImGui::Spacing();

            // --- Gravity Vector Adjuster ---
            static float gravity[2] = { 0.0f, -9.81f };
            ImGui::SliderFloat2("Gravity (m/s²)", gravity, -20.0f, 20.0f, "%.1f");

            ImGui::Spacing();
            ImGui::Separator();

            // --- Entity Spawner / Clear ---
            if (ImGui::Button("Spawn +50 Balls")) {
                // Signal ball creation
            }
            ImGui::SameLine();
            if (ImGui::Button("Clear All")) {
                // Signal entity wipe
            }
        }
        ImGui::End();
    }
}

void MetricsOverlay::endFrame() const {
    if (!m_initialized) return;

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void MetricsOverlay::draw() const {
    if (!m_initialized) return;

    beginFrame();
    render();
    endFrame();
}

} // namespace render