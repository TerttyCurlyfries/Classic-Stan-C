#include <pebble.h>

static Window *w_main_window;
static Window *w_action_window;
static BitmapLayer *w_background_layer;
static GBitmap *w_background_bitmap;
static GFont w_time_font;
static TextLayer *w_time_layer, *w_date_layer;
static TextLayer *w_top_layer, *w_middle_top_layer, *w_middle_middle_layer, *w_middle_bottom_layer, *w_bottom_layer;

static void update_time() {
  // Get a tm structure
  time_t temp = time(NULL); 
  struct tm *tick_time = localtime(&temp);

  // Write the current hours and minutes into a buffer
  static char buffer[] = "00:00";
  if(clock_is_24h_style()) {
    strftime(buffer, sizeof("00:00"), "%H:%M", tick_time);
  } else {
    strftime(buffer, sizeof(buffer), "%I:%M", tick_time);
  if('0' == buffer[0]) {
    memmove(buffer, &buffer[1], sizeof(buffer)-1);
  }
  //strftime(ampm_buffer, sizeof(ampm_buffer), "%p", tick_time);
  }

  // Display this time on the TextLayer
  text_layer_set_text(w_time_layer, buffer);
  
  static char date_buffer[16];
  strftime(date_buffer, sizeof(date_buffer), "%b %d", tick_time);
  // Show the date
  text_layer_set_text(w_date_layer, date_buffer);
}

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  update_time();
}

static void watchmain_window_load(Window *window) {
  // Get information about the Window
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  // Create GBitmap
  w_background_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BACKGROUND_PNG);
  // Create BitmapLayer to display the GBitmap
  w_background_layer = bitmap_layer_create(bounds);
  // Set the bitmap onto the layer and add to the window
  bitmap_layer_set_bitmap(w_background_layer, w_background_bitmap);
  layer_add_child(window_layer, bitmap_layer_get_layer(w_background_layer));
  
  // Create date TextLayer
  w_date_layer = text_layer_create(GRect(42, 145, 144, 30));
  text_layer_set_text_color(w_date_layer, GColorBlack);
  text_layer_set_background_color(w_date_layer, GColorClear);
  text_layer_set_text_alignment(w_date_layer, GTextAlignmentCenter);
  w_time_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_ROBOTO_CONDENSED_16));
  text_layer_set_font(w_date_layer, w_time_font);
  // Add to Window
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(w_date_layer));
  
  w_top_layer = text_layer_create(GRect(44, 0, 80, 50));
  text_layer_set_text_color(w_top_layer, GColorBlack);
  text_layer_set_background_color(w_top_layer, GColorClear);
  text_layer_set_text(w_top_layer, "IF");
  text_layer_set_text_alignment(w_top_layer, GTextAlignmentCenter);
  text_layer_set_font(w_top_layer, w_time_font);
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(w_top_layer));
  
  w_middle_top_layer = text_layer_create(GRect(70, 17, 80, 50));
  text_layer_set_text_color(w_middle_top_layer, GColorBlack);
  text_layer_set_background_color(w_middle_top_layer, GColorClear);
  text_layer_set_text(w_middle_top_layer, "HAD A");
  text_layer_set_text_alignment(w_middle_top_layer, GTextAlignmentCenter);
  text_layer_set_font(w_middle_top_layer, w_time_font);
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(w_middle_top_layer));
  
  w_middle_middle_layer = text_layer_create(GRect(70, 32, 80, 50));
  text_layer_set_text_color(w_middle_middle_layer, GColorBlack);
  text_layer_set_background_color(w_middle_middle_layer, GColorClear);
  text_layer_set_text(w_middle_middle_layer, "FACE, I");
  text_layer_set_text_alignment(w_middle_middle_layer, GTextAlignmentCenter);
  text_layer_set_font(w_middle_middle_layer, w_time_font);
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(w_middle_middle_layer));
  
  w_middle_bottom_layer = text_layer_create(GRect(69, 48, 80, 50));
  text_layer_set_text_color(w_middle_bottom_layer, GColorBlack);
  text_layer_set_background_color(w_middle_bottom_layer, GColorClear);
  text_layer_set_text(w_middle_bottom_layer, "WOULD");
  text_layer_set_text_alignment(w_middle_bottom_layer, GTextAlignmentCenter);
  text_layer_set_font(w_middle_bottom_layer, w_time_font);
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(w_middle_bottom_layer));
  
  w_bottom_layer = text_layer_create(GRect(70, 64, 80, 50));
  text_layer_set_text_color(w_bottom_layer, GColorBlack);
  text_layer_set_background_color(w_bottom_layer, GColorClear);
  text_layer_set_text(w_bottom_layer, "PUNCH IT!");
  text_layer_set_text_alignment(w_bottom_layer, GTextAlignmentCenter);
  text_layer_set_font(w_bottom_layer, w_time_font);
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(w_bottom_layer));
  
  // Create the TextLayer with specific bounds
  w_time_layer = text_layer_create(GRect(75, 0, 80, 50));
  text_layer_set_background_color(w_time_layer, GColorClear);
  text_layer_set_text_color(w_time_layer, GColorBlack);
  text_layer_set_text(w_time_layer, "00:00");
  text_layer_set_text_alignment(w_time_layer, GTextAlignmentCenter);
  text_layer_set_font(w_time_layer, w_time_font);

  // Add it as a child layer to the Window's root layer
  layer_add_child(window_layer, text_layer_get_layer(w_time_layer));
  }

static void watchmain_window_unload(Window *window) {
  // Destroy TextLayer
  text_layer_destroy(w_time_layer);
  text_layer_destroy(w_date_layer);
  text_layer_destroy(w_top_layer);
  text_layer_destroy(w_middle_top_layer);
  text_layer_destroy(w_middle_middle_layer);
  text_layer_destroy(w_middle_bottom_layer);
  text_layer_destroy(w_bottom_layer);
  fonts_unload_custom_font(w_time_font);
  
  gbitmap_destroy(w_background_bitmap);
  bitmap_layer_destroy(w_background_layer);

}


/*static void tap_handler(AccelAxisType axis, int32_t direction){
  
if((axis == ACCEL_AXIS_X) || (axis == ACCEL_AXIS_Y)){
  APP_LOG(APP_LOG_LEVEL_INFO, "Yo");
  if((direction > -1)){
    window_stack_push(w_action_window, true);
    APP_LOG(APP_LOG_LEVEL_INFO, "Ur shaking up my world ;)");
    }
  }
}


  static void action_window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);  
  
  w_time_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_ROBOTO_CONDENSED_16));
  
  s_time_layer = text_layer_create(GRect(75, 0, 80, 50));
  text_layer_set_background_color(s_time_layer, GColorClear);
  text_layer_set_text_color(s_time_layer, GColorBlack);
  text_layer_set_text(s_time_layer, "00:00");
  text_layer_set_text_alignment(s_time_layer, GTextAlignmentCenter);
  text_layer_set_font(s_time_layer, s_time_font);

  // Add it as a child layer to the Window's root layer
  layer_add_child(window_layer, text_layer_get_layer(s_time_layer));
}

static void action_window_unload(Window *window) {
  
  fonts_unload_custom_font(s_time_font);
  
  text_layer_destroy(s_time_layer);
}

*/
static void watchinit() {
  // Create main Window element and assign to pointer
  w_main_window = window_create();
  
 // w_action_window = window_create();

  // Set handlers to manage the elements inside the Window
  window_set_window_handlers(w_main_window, (WindowHandlers) {
    .load = watchmain_window_load,
    .unload = watchmain_window_unload
  });
  
/*  window_set_window_handlers(w_action_window, (WindowHandlers) {
    .load = action_window_load,
    .unload = action_window_unload
  });
*/
  // Show the Window on the watch, with animated=true
  window_stack_push(w_main_window, true);

  // Make sure the time is displayed from the start
  update_time();
  
  // Register with TickTimerService
  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
  
  //Accel service
  //accel_tap_service_subscribe(tap_handler);
}

static void watchdeinit() {
  // Destroy Window
  accel_tap_service_unsubscribe();
  window_destroy(w_main_window);
  window_destroy(w_action_window);
}

/*int main(void) {
  init();
  app_event_loop();
  deinit();
}
*/