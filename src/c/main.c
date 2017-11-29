#include <pebble.h>
#include "watch.c"
#include "menu.c"

//Pebble.js variables
#define KEY_TEMPERATURE 0
#define KEY_CONDITIONS 1

//Splash Vars
static Window *s_splash_window;
static BitmapLayer *s_background_layer;
static GBitmap *s_background_bitmap;
static TextLayer *s_splash_text;

//Hub Vars
static Window *s_hub_window;
static TextLayer *s_hub_text;
ActionBarLayer *action_bar;

//Settings Vars
static Window *s_settings_window;
static TextLayer *s_settings_text;
static Layer *s_rectangle_layer;

//Thing for timer to do once it runs out? Idk it works though
void test(void * data){
  window_stack_push(s_hub_window, true);
  window_stack_remove(s_splash_window, false);
}
//Button configs

void hub_up_single_click_handler(ClickRecognizerRef recognizer, void *context) {
  watchinit();
}


void hub_select_single_click_handler(ClickRecognizerRef recognizer, void *context) {
  window_stack_push(s_menu_window, true);
}

void hub_down_single_click_handler(ClickRecognizerRef recognizer, void *context) {
  window_stack_push(s_settings_window, true);
}

void settings_down_single_click_handler(ClickRecognizerRef recognizer, void *context) {

}

void hub_config_provider(Window *window) {
 window_single_click_subscribe(BUTTON_ID_UP, hub_up_single_click_handler);
 window_single_click_subscribe(BUTTON_ID_SELECT, hub_select_single_click_handler);
 window_single_click_subscribe(BUTTON_ID_DOWN, hub_down_single_click_handler);
}

void settings_config_provider(Window *window) {
// window_single_click_subscribe(BUTTON_ID_UP, up_single_click_handler);
// window_single_click_subscribe(BUTTON_ID_SELECT, select_single_click_handler);
 window_single_click_subscribe(BUTTON_ID_DOWN, settings_down_single_click_handler);
}

static void main_window_load(Window *window) {
  // Get information about the Window
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);
  window_set_background_color(s_splash_window, GColorBlack);
  
  s_background_layer = bitmap_layer_create(bounds);
  
  bitmap_layer_set_bitmap(s_background_layer, s_background_bitmap);
  layer_add_child(window_layer, bitmap_layer_get_layer(s_background_layer));


  s_splash_text = text_layer_create(GRect(0, 65, 144, 30));
  text_layer_set_text_color(s_splash_text, GColorWhite);
  text_layer_set_background_color(s_splash_text, GColorClear);
  text_layer_set_text(s_splash_text, "Hi ho!");
  text_layer_set_text_alignment(s_splash_text, GTextAlignmentCenter);
  text_layer_set_font(s_splash_text, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
  // Add to Window
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_splash_text));
  
}

static void main_window_unload(Window *window) {
  // Destroy TextLayer
  text_layer_destroy(s_splash_text);
  bitmap_layer_destroy(s_background_layer);

}

//Sub for action bar
void hub_click_config_provider(void *context) {
  //HUB THINGS
  window_single_click_subscribe(BUTTON_ID_UP, (ClickHandler) hub_up_single_click_handler);
  window_single_click_subscribe(BUTTON_ID_SELECT, (ClickHandler) hub_select_single_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, (ClickHandler) hub_down_single_click_handler);
 // window_single_click_subscribe(BUTTON_ID_UP, (ClickHandler) my_previous_click_handler);

}

void settings_click_config_provider(void *context) {
  //SETTINGS THINGS
  window_single_click_subscribe(BUTTON_ID_DOWN, (ClickHandler) settings_down_single_click_handler);
}

static void hub_window_load(Window *window) {
  
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);
  window_set_background_color(s_hub_window, GColorWhite);
  
  s_background_layer = bitmap_layer_create(bounds);
  
  bitmap_layer_set_bitmap(s_background_layer, s_background_bitmap);
  layer_add_child(window_layer, bitmap_layer_get_layer(s_background_layer));
  
  s_hub_text = text_layer_create(GRect(-20, 65, 144, 30));
  text_layer_set_text_color(s_hub_text, GColorBlack);
  text_layer_set_background_color(s_hub_text, GColorClear);
  text_layer_set_text(s_hub_text, "Stan here!");
  text_layer_set_text_alignment(s_hub_text, GTextAlignmentCenter);
  text_layer_set_font(s_hub_text, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
  // Add to Window
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_hub_text));
  
  //Action Bar
  
  // Initialize the action bar:
  action_bar = action_bar_layer_create();
  // Associate the action bar with the window:
  action_bar_layer_add_to_window(action_bar, window);
  // Set the click config provider:
  action_bar_layer_set_click_config_provider(action_bar,
                                             hub_click_config_provider);
  
}

static void hub_window_unload(Window *window) {
}

static void canvas_update_proc(Layer *layer, GContext *ctx) {
GRect rect_bounds = GRect(0, 0, 120, 170);
  
graphics_context_set_fill_color(ctx, GColorWhite);
graphics_fill_rect(ctx, rect_bounds, 8, 8);
// Draw a rectangle
graphics_draw_rect(ctx, rect_bounds);

}

static void settings_window_load(Window *window) {
  
  Layer *window_layer = window_get_root_layer(window);
  window_set_background_color(s_hub_window, GColorBlack);
  
  GRect bounds = layer_get_bounds(window_get_root_layer(window));

  // Create canvas layer
  s_rectangle_layer = layer_create(bounds);
  
  s_background_layer = bitmap_layer_create(bounds);
  
  // Assign the custom drawing procedure
  layer_set_update_proc(s_rectangle_layer, canvas_update_proc);

// Add to Window
  layer_add_child(window_get_root_layer(window), s_rectangle_layer);
  layer_mark_dirty(s_rectangle_layer);
  bitmap_layer_set_bitmap(s_background_layer, s_background_bitmap);
  layer_add_child(window_layer, bitmap_layer_get_layer(s_background_layer));
  
  s_settings_text = text_layer_create(GRect(-20, 65, 144, 30));
  text_layer_set_text_color(s_settings_text, GColorBlack);
  text_layer_set_background_color(s_settings_text, GColorClear);
  text_layer_set_text(s_settings_text, "Quicklaunch");
  text_layer_set_text_alignment(s_settings_text, GTextAlignmentCenter);
  text_layer_set_font(s_settings_text, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
  // Add to Window
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_settings_text));
  
    //Action Bar
  
  // Initialize the action bar:
  action_bar = action_bar_layer_create();
  // Associate the action bar with the window:
  action_bar_layer_add_to_window(action_bar, window);
  // Set the click config provider:
  action_bar_layer_set_click_config_provider(action_bar,
                                             settings_click_config_provider);
}

static void settings_window_unload(Window *window) {
  // Destroy TextLayer
  
}

static void inbox_received_callback(DictionaryIterator *iterator, void *context) {

  // Store incoming information
  static char temperature_buffer[8];
  static char conditions_buffer[32];
  static char weather_layer_buffer[32];

  // Read tuples for data
  Tuple *temp_tuple = dict_find(iterator, KEY_TEMPERATURE);
  Tuple *conditions_tuple = dict_find(iterator, KEY_CONDITIONS);

  // If all data is available, use it
  if(temp_tuple && conditions_tuple) {
    snprintf(temperature_buffer, sizeof(temperature_buffer), "%dC", (int)temp_tuple->value->int32);
    snprintf(conditions_buffer, sizeof(conditions_buffer), "%s", conditions_tuple->value->cstring);

    // Assemble full string and display
    snprintf(weather_layer_buffer, sizeof(weather_layer_buffer), "%s, %s", temperature_buffer, conditions_buffer);
    text_layer_set_text(s_voice_text, weather_layer_buffer);
  }
}

static void inbox_dropped_callback(AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_ERROR, "Message dropped!");
}

static void outbox_failed_callback(DictionaryIterator *iterator, AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_ERROR, "Outbox send failed!");
}

static void outbox_sent_callback(DictionaryIterator *iterator, void *context) {
  APP_LOG(APP_LOG_LEVEL_INFO, "Outbox send success!");
}


static void init() {
  // Create main Window element and assign to pointer
  s_splash_window = window_create();
  
  // Set handlers to manage the elements inside the Window
  window_set_window_handlers(s_splash_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload
  });
  
  window_stack_push(s_splash_window, true);
  
  //Creating hub
  s_hub_window = window_create();
  
  window_set_click_config_provider(s_hub_window, (ClickConfigProvider) hub_config_provider);
    
  window_set_window_handlers(s_hub_window, (WindowHandlers) {
    .load = hub_window_load,
    .unload = hub_window_unload
  });
  
  //Hi Ho timer
  app_timer_register(1000, test, NULL);
  
  //creating voice located in voice.c
  s_voice_window = window_create();
    
  window_set_click_config_provider(s_voice_window, (ClickConfigProvider) voice_config_provider);
  
  window_set_window_handlers(s_voice_window, (WindowHandlers) {
    .load = voice_window_load,
    .unload = voice_window_unload
  });
  
  //creating menu located in menu.c
  s_menu_window = window_create();
  
  //window_set_click_config_provider(s_settings_window, (ClickConfigProvider) menu_config_provider);
    
  window_set_window_handlers(s_menu_window, (WindowHandlers) {
    .load = menu_window_load,
    .unload = menu_window_unload
  });
  
  //creating settings
  s_settings_window = window_create();
  
  window_set_click_config_provider(s_settings_window, (ClickConfigProvider) settings_config_provider);
    
  window_set_window_handlers(s_settings_window, (WindowHandlers) {
    .load = settings_window_load,
    .unload = settings_window_unload
  });
  
  // Register callbacks
app_message_register_inbox_received(inbox_received_callback);
app_message_register_inbox_dropped(inbox_dropped_callback);
app_message_register_outbox_failed(outbox_failed_callback);
app_message_register_outbox_sent(outbox_sent_callback);

//app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());
}

static void deinit() {
  // Destroy Window
  window_destroy(s_splash_window);
  window_destroy(s_hub_window);
  window_destroy(s_settings_window);
}

int main(void) {
  init();
 // watchinit();
  app_event_loop();
  deinit();
  watchdeinit();
}