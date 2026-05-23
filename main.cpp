#include <stdio.h>
#include <string.h>
#include <math.h>

#include <GL/glew.h>

#include "ogldev_basic_glfw_camera.h"
#include "ogldev_basic_lighting.h"
#include "ogldev_basic_mesh.h"
#include "ogldev_engine_common.h"
#include "ogldev_framebuffer.h"
#include "ogldev_glfw.h"
#include "ogldev_math_3d.h"
// #include "ogldev_new_lighting.h"
#include "ogldev_shadow_mapping_technique.h"

#define WINDOW_WIDTH 2560
#define WINDOW_HEIGHT 1600
#define SHADOW_MAP_WIDTH 2048
#define SHADOW_MAP_HEIGHT 2048

const bool fullscreen = true;

static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
static void CursorPosCallback(GLFWwindow* window, double x, double y);
static void MouseButtonCallback(GLFWwindow* window, int Button, int Action, int Mode);

class Tutorial35
{
public:

    Tutorial35()
    {
        // m_spotLight.WorldPosition  = Vector3f(-20.0, 20.0, 0.0f);
        // m_spotLight.WorldDirection = Vector3f(1.0f, -1.0f, 0.0f);
        m_spotLight.Position  = Vector3f(-20.0, 20.0, 0.0f);
        m_spotLight.Direction = Vector3f(1.0f, -1.0f, 0.0f);
        m_spotLight.DiffuseIntensity = 0.9f;
        m_spotLight.AmbientIntensity = 0.2f;
        m_spotLight.Color = Vector3f(1.0f, 1.0f, 1.0f);
        m_spotLight.Attenuation.Linear = 0.00f;
        m_spotLight.Attenuation.Exp = 0.0f;
        m_spotLight.Cutoff = 30.0f;

        // Initialize a perspective projection matrix for the spot light
        float FOV = 45.0f;
        float zNear = 1.0f;
        float zFar = 50.0f;
        PersProjInfo shadowPersProjInfo = { FOV, SHADOW_MAP_WIDTH, SHADOW_MAP_HEIGHT, zNear, zFar };
        m_lightPersProjMatrix.InitPersProjTransform(shadowPersProjInfo);
    }

    virtual ~Tutorial35()
    {
        SAFE_DELETE(m_pGameCamera);
        SAFE_DELETE(m_pMesh1);
        SAFE_DELETE(m_pTerrain);
    }

    void Init()
    {
        CreateWindow();

        CreateShadowMap();

        InitCallbacks();

        // on MacOS you need to load VAO before compiling the shader otherwise you get:
        // `Validation Failed: No vertex array object bound`
        InitMesh();

        InitCamera();

        InitShaders();
    }

    void Run()
    {
        while (!glfwWindowShouldClose(window)) {
            RenderSceneCB();
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }

    void RenderSceneCB()
    {
        ShadowMapPass();
        LightingPass();
    }

    void ShadowMapPass()
    {
        // m_shadowMapFBO.BindForWriting();
        //
        // glClear(GL_DEPTH_BUFFER_BIT);
        //
        // m_shadowMapTech.Enable();
        //
        // Matrix4f World = m_pMesh1->GetWorldMatrix();
        //
        // Matrix4f LightView;
        // Vector3f Up(0.0f, 1.0f, 0.0f);
        // // LightView.InitCameraTransform(m_spotLight.WorldPosition, m_spotLight.WorldDirection, Up);
        // LightView.InitCameraTransform(m_spotLight.Position, m_spotLight.Direction, Up);
        //
        // Matrix4f WVP = m_lightPersProjMatrix * LightView * World;
        // m_shadowMapTech.SetWVP(WVP);
        //
        // m_pMesh1->Render();
    }

    void LightingPass()
    {
        // glBindFramebuffer(GL_FRAMEBUFFER, 0);

        glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        m_lightingTech.Enable();

        // m_shadowMapFBO.BindDepthForReading(SHADOW_TEXTURE_UNIT);

        m_pGameCamera->OnRender();

        static float foo = 0.0f;
        foo += 0.002f;

        // m_spotLight.WorldPosition = Vector3f(-sinf(foo) * 15.0f, 8.0f, -cosf(foo) * 15.0f);
        // m_spotLight.WorldDirection = m_pMesh1->GetPosition() - m_spotLight.WorldPosition;
        m_spotLight.Position = Vector3f(-sinf(foo) * 15.0f, 8.0f, -cosf(foo) * 15.0f);
        m_spotLight.Direction = m_pMesh1->GetPosition() - m_spotLight.Position;


        if (m_cameraOnLight) {
            // m_pGameCamera->SetPosition(m_spotLight.WorldPosition);
            // m_pGameCamera->SetTarget(m_spotLight.WorldDirection);
            m_pGameCamera->SetPosition(m_spotLight.Position);
            m_pGameCamera->SetTarget(m_spotLight.Direction);
        }

        ///////////////////////////
        // Render the main object
        ////////////////////////////

        // Set the WVP matrix from the camera point of view
        Matrix4f World = m_pMesh1->GetWorldMatrix();
        Matrix4f CameraView = m_pGameCamera->GetMatrix();
        Matrix4f CameraProjection = m_pGameCamera->GetProjectionMat();
        Matrix4f WVP = CameraProjection * CameraView * World;
        m_lightingTech.SetWVP(WVP);

        // Set the WVP matrix from the light point of view
        // Matrix4f LightView;
        // Vector3f Up(0.0f, 1.0f, 0.0f);
        // LightView.InitCameraTransform(m_spotLight.WorldPosition, m_spotLight.WorldDirection, Up);
        // Matrix4f LightWVP = m_lightPersProjMatrix * LightView * World;
        // m_lightingTech.SetLightWVP(LightWVP);
        //
        // Vector3f CameraLocalPos3f = m_pMesh1->GetWorldTransform().WorldPosToLocalPos(m_pGameCamera->GetPos());
        // m_lightingTech.SetCameraLocalPos(CameraLocalPos3f);
        //
        // m_spotLight.CalcLocalDirectionAndPosition(m_pMesh1->GetWorldTransform());

        m_lightingTech.SetSpotLights(1, &m_spotLight);

        // m_lightingTech.SetMaterial(m_pMesh1->GetMaterial());

        m_pMesh1->Render();

        /////////////////////////
        // Render the terrain
        ////////////////////////

        // Set the WVP matrix from the camera point of view
        World = m_pTerrain->GetWorldMatrix();
        WVP = CameraProjection * CameraView * World;
        m_lightingTech.SetWVP(WVP);

        // Set the WVP matrix from the light point of view
        // LightWVP = m_lightPersProjMatrix * LightView * World;
        // m_lightingTech.SetLightWVP(LightWVP);

        // Update the shader with the local space pos/dir of the spot light
        // m_spotLight.CalcLocalDirectionAndPosition(m_pTerrain->GetWorldTransform());
        // m_lightingTech.SetSpotLights(1, &m_spotLight);
        // m_lightingTech.SetMaterial(m_pTerrain->GetMaterial());

        // Update the shader with the local space pos of the camera
        // CameraLocalPos3f = m_pTerrain->GetWorldTransform().WorldPosToLocalPos(m_pGameCamera->GetPos());
        // m_lightingTech.SetCameraLocalPos(CameraLocalPos3f);

        m_pTerrain->Render();
    }

#define ATTEN_STEP 0.01f

#define ANGLE_STEP 1.0f


    void KeyboardCB(uint key, int state)
    {
        if (state == GLFW_PRESS) {
            switch (key) {
            case GLFW_KEY_ESCAPE:
            case GLFW_KEY_Q:
                glfwDestroyWindow(window);
                glfwTerminate();
                exit(0);

            case GLFW_KEY_L:
                m_cameraOnLight = !m_cameraOnLight;
                if (!m_cameraOnLight) {
                    m_pGameCamera->SetPosition(m_cameraPos);
                    m_pGameCamera->SetTarget(m_cameraTarget);
                }
                break;

            case GLFW_KEY_A:
                m_spotLight.Attenuation.Linear += ATTEN_STEP;
                m_spotLight.Attenuation.Linear += ATTEN_STEP;
                break;

            case GLFW_KEY_Z:
                m_spotLight.Attenuation.Linear -= ATTEN_STEP;
                m_spotLight.Attenuation.Linear -= ATTEN_STEP;
                break;

            case GLFW_KEY_S:
                m_spotLight.Attenuation.Exp += ATTEN_STEP;
                m_spotLight.Attenuation.Exp += ATTEN_STEP;
                break;

            case GLFW_KEY_X:
                m_spotLight.Attenuation.Exp -= ATTEN_STEP;
                m_spotLight.Attenuation.Exp -= ATTEN_STEP;
                break;
            }
        }
    }

    void PassiveMouseCB(int x, int y)
    {
        m_pGameCamera->OnMouse(x, y);
    }

    void MouseCB(int button, int action, int x, int y)
    {
    }

private:

    void CreateWindow()
    {
#ifdef __APPLE__
        // MacOS is capped at opengl 4.1
        int major_ver = 4;
        int minor_ver = 1;
#else
        int major_ver = 0;
        int minor_ver = 0;
#endif
        window = glfw_init(major_ver, minor_ver, WINDOW_WIDTH, WINDOW_HEIGHT, fullscreen, "Tutorial 35");
        glfwSetCursorPos(window, WINDOW_WIDTH / 2.0, WINDOW_HEIGHT / 2.0);
    }

    void CreateShadowMap()
    {
        // m_shadowMapFBO.Init(SHADOW_MAP_WIDTH, SHADOW_MAP_HEIGHT, 0, false, true, false);
    }

    void InitCallbacks()
    {
        glfwSetKeyCallback(window, KeyCallback);
        glfwSetCursorPosCallback(window, CursorPosCallback);
        glfwSetMouseButtonCallback(window, MouseButtonCallback);
    }

    void InitCamera()
    {
        m_cameraPos = Vector3f(3.0f, 3.0f, -15.0f);
        m_cameraTarget = Vector3f(-0.2f, -0.2f, 1.0f);
        Vector3f Up(0.0, 1.0f, 0.0f);

        float FOV = 45.0f;
        float zNear = 1.0f;
        float zFar = 100.0f;
        PersProjInfo persProjInfo = { FOV, (float)WINDOW_WIDTH, (float)WINDOW_HEIGHT, zNear, zFar };

        m_pGameCamera = new BasicCamera(persProjInfo, m_cameraPos, m_cameraTarget, Up);
    }

    void InitShaders()
    {
        if (!m_lightingTech.Init()) {
            printf("Error initializing the lighting technique\n");
            exit(1);
        }

        m_lightingTech.Enable();
        // m_lightingTech.SetTextureUnit(COLOR_TEXTURE_UNIT_INDEX);
        // m_lightingTech.SetShadowMapTextureUnit(SHADOW_TEXTURE_UNIT_INDEX);
        //    m_lightingTech.SetSpecularExponentTextureUnit(SPECULAR_EXPONENT_UNIT_INDEX);

        // if (!m_shadowMapTech.Init()) {
        //     printf("Error initializing the shadow mapping technique\n");
        //     exit(1);
        // }
    }

    void InitMesh()
    {
        m_pMesh1 = new BasicMesh();

        m_pMesh1->LoadMesh("./content/ordinary_house/ordinary_house.obj");

        m_pTerrain = new BasicMesh();
        m_pTerrain->LoadMesh("./content/box_terrain.obj");
        m_pTerrain->SetPosition(0.0f, 0.0f, 0.0f);
    }

    GLFWwindow* window = NULL;
    BasicLightingTechnique m_lightingTech;
    // ShadowMappingTechnique m_shadowMapTech;
    BasicCamera* m_pGameCamera = NULL;
    BasicMesh* m_pMesh1 = NULL;
    BasicMesh* m_pTerrain = NULL;
    PersProjInfo persProjInfo;
    Matrix4f m_lightPersProjMatrix;
    SpotLight m_spotLight;
    // Framebuffer m_shadowMapFBO;
    Vector3f m_cameraPos;
    Vector3f m_cameraTarget;
    bool m_cameraOnLight = false;
};

Tutorial35* app = NULL;

static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    app->KeyboardCB(key, action);
}

static void CursorPosCallback(GLFWwindow* window, double x, double y)
{
    app->PassiveMouseCB((int)x, (int)y);
}

static void MouseButtonCallback(GLFWwindow* window, int Button, int Action, int Mode)
{
    double x, y;

    glfwGetCursorPos(window, &x, &y);

    app->MouseCB(Button, Action, (int)x, (int)y);
}

int main(int argc, char** argv)
{
    app = new Tutorial35();

    printf("new app\n");
    app->Init();

    printf("app init\n");
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glFrontFace(GL_CW);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    printf("gl methods\n");
    app->Run();

    delete app;

    return 0;
}
