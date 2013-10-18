#include "testApp.h"


/**
 http://wiki.awesomium.com/getting-started/setting-up-on-macosx.html
 https://github.com/paulhoux/Cinder-Awesomium
 */

//--------------------------------------------------------------
void testApp::setup(){
    ofSetWindowShape(WIDTH, HEIGHT);
    
    WebConfig config;
    config.log_path = WSLit(ofToDataPath("Logs").c_str());
    config.log_level = kLogLevel_Verbose; //kLogLevel_Normal;
    
    web_core = WebCore::Initialize(config);
    
    WebPreferences prefs;
    prefs.enable_plugins = true;
    prefs.enable_smooth_scrolling = true;
    
    my_session = web_core->CreateWebSession(WSLit(ofToDataPath("SessionData").c_str()), prefs);
    
    
    web_view = web_core->CreateWebView(WIDTH, HEIGHT, my_session);
    web_view->LoadURL(WebURL(WSLit("http://youtube.com")));
    web_view->Focus();
    //web_view->ExecuteJavascriptWithResult(WSLit("reset()"), WSLit(""));
    
    texture.allocate(WIDTH, HEIGHT, GL_RGBA);
}

//--------------------------------------------------------------
void testApp::exit(){
    web_view->Destroy();
    WebCore::Shutdown();
}


//--------------------------------------------------------------
void testApp::update(){
    web_core->Update();
    
    char title[1024];
    web_view->title().ToUTF8( title, 1024 );
    ofSetWindowTitle(title);
    
    
    surface = (BitmapSurface*)web_view->surface();
    
    if(surface && surface->buffer() && surface->is_dirty())
    {
        texture.loadData(surface->buffer(), WIDTH, HEIGHT, GL_BGRA);
    }
}

//--------------------------------------------------------------
void testApp::draw(){
    ofSetColor(ofColor::white);
    texture.draw(pos, WIDTH, HEIGHT);
}


//--------------------------------------------------------------
void testApp::keyPressed(int key){
    // view->Cut();
    // view->Copy();
    // view->Paste();
    
    web_view->Focus();
    
    Awesomium::WebKeyboardEvent keyDown;
    keyDown.type = Awesomium::WebKeyboardEvent::kTypeKeyDown;
    keyDown.virtual_key_code = (char)key;
    keyDown.native_key_code = (char)key;
    keyDown.text[0] = (char)key;
    keyDown.unmodified_text[0] = (char)key;
    keyDown.modifiers = 0;
    // keyDown.modifiers  ???
    web_view->InjectKeyboardEvent( keyDown );
    
    
    Awesomium::WebKeyboardEvent typeChar;
    typeChar.type = Awesomium::WebKeyboardEvent::kTypeChar;
    typeChar.virtual_key_code =  (char)key;
    typeChar.native_key_code =  (char)key;
    typeChar.text[0] =  (char)key;
    typeChar.unmodified_text[0] =  (char)key;
    web_view->InjectKeyboardEvent( typeChar );
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    web_view->Focus();
    

    Awesomium::WebKeyboardEvent evt;
    evt.type = Awesomium::WebKeyboardEvent::kTypeKeyUp;
    evt.virtual_key_code = (char)key;
    evt.native_key_code = (char)key;
    evt.text[0] = (char)key;
    evt.unmodified_text[0] = (char)key;
    evt.modifiers = 0;
    web_view->InjectKeyboardEvent( evt );
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
    web_view->InjectMouseMove( x+pos.x, y+pos.y );
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    web_view->InjectMouseMove( x+pos.x, y+pos.y );
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    
    if( button ==  OF_MOUSE_BUTTON_1)
        web_view->InjectMouseDown( Awesomium::kMouseButton_Left );
    else if( button == OF_MOUSE_BUTTON_2 )
        web_view->InjectMouseDown( Awesomium::kMouseButton_Middle );
    else if( button== OF_MOUSE_BUTTON_3 )
        web_view->InjectMouseDown( Awesomium::kMouseButton_Right );
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    
    if( button ==  OF_MOUSE_BUTTON_1)
        web_view->InjectMouseUp( Awesomium::kMouseButton_Left );
    else if( button == OF_MOUSE_BUTTON_2 )
        web_view->InjectMouseUp( Awesomium::kMouseButton_Middle );
    else if( button== OF_MOUSE_BUTTON_3 )
        web_view->InjectMouseUp( Awesomium::kMouseButton_Right );
}


//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
    // resize webview if window resizes
    if( web_view )
        web_view->Resize( w, h );
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
