#include "inexor/ui/cefapp.h"

InexorCefApp::InexorCefApp(int width, int height)
{
    layer_manager = new InexorCefLayerManager(width, height);
    mouse_manager = new InexorCefMouseManager(layer_manager);
    keyboard_manager = new InexorCefKeyboardManager(layer_manager);
    console = new InexorCefConsole();
    menu = new InexorCefMenu();
    debug_overlay = new InexorCefDebugOverlay();
    context_manager = new InexorCefContextManager();
    layer_manager->AddLayerProvider(console);
    layer_manager->AddLayerProvider(menu);
    layer_manager->AddLayerProvider(debug_overlay);
    context_manager->AddSubContext(mouse_manager);
    context_manager->AddSubContext(keyboard_manager);
    context_manager->AddSubContext(layer_manager);
    context_manager->AddSubContext(console);
    context_manager->AddSubContext(menu);
    context_manager->AddSubContext(debug_overlay);
    SetScreenSize(width, height);
    mouse_manager->Show();
}

void InexorCefApp::Destroy()
{
    layer_manager->DestroyLayers();
}

void InexorCefApp::Render()
{
    layer_manager->Render();
    mouse_manager->Render();
}

void InexorCefApp::SetScreenSize(int width, int height) {
    mouse_manager->SetMax(width, height);
    layer_manager->SetScreenSize(width, height);
}

void InexorCefApp::OnContextInitialized()
{
    CEF_REQUIRE_UI_THREAD();
    layer_manager->InitializeLayers();
}

void InexorCefApp::OnContextCreated(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefV8Context> browser_context)
{
    // cefdebug("InexorCefApp::OnContextCreated", "Injecting inexor object into javascript context");
    browser_context->GetGlobal()->SetValue(context_manager->GetContextName(), context_manager->GetContext(), V8_PROPERTY_ATTRIBUTE_NONE);
}

bool InexorCefApp::handle_sdl_event(SDL_Event ev) {
    switch(ev.type) {
      case SDL_TEXTINPUT:
      case SDL_KEYDOWN:
      case SDL_KEYUP:
        GetKeyboardManager()->SendKeyEvent(ev);
        return true;

      case SDL_MOUSEMOTION:
        GetMouseManager()->SendMouseMoveEvent(ev);
        return true;

      case SDL_MOUSEBUTTONDOWN:
      case SDL_MOUSEBUTTONUP:
        GetMouseManager()->SendMouseClickEvent(ev);
        return true;

      case SDL_MOUSEWHEEL:
        GetMouseManager()->SendMouseWheelEvent(ev);
        return true;

      default:
        return false;
    }
}