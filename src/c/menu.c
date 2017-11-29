#include <pebble.h>

#define NUM_MENU_SECTIONS 2
#define NUM_FIRST_MENU_ITEMS 4

typedef enum {
  spanishSpeak,
  frenchSpeak,
  germanSpeak,
  finnishSpeak
} helloType;

typedef struct {
  helloType type;
} Context;

//Menu Vars
static Window *s_menu_window;
MenuLayer *menu_layer;
static SimpleMenuLayer *s_simple_menu_layer;
static SimpleMenuSection s_menu_sections[NUM_MENU_SECTIONS];
static SimpleMenuItem s_first_menu_items[NUM_FIRST_MENU_ITEMS];
static GBitmap *s_menu_icon_image;

static TextLayer *s_voice_text;
char *displayText;
static helloType s_current_type;

//Voice window vars
static Window *s_voice_window;
static BitmapLayer *s_background_layer;
static GBitmap *s_background_bitmap;
static ActionMenu *s_action_menu;
static ActionMenuLevel *action_menu;

//VOIIIIIICE
static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
  // Configure the ActionMenu Window about to be shown
  ActionMenuConfig config = (ActionMenuConfig) {
    .root_level = action_menu,
    .colors = {
      .background = PBL_IF_COLOR_ELSE(GColorChromeYellow, GColorWhite),
      .foreground = GColorBlack,
    },
    .align = ActionMenuAlignCenter
  };

  // Show the ActionMenu
  s_action_menu = action_menu_open(&config);
}

static void voice_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
}

static void hello_performed_callback(ActionMenu *action_menu, const ActionMenuItem *action, void *context) {

  s_current_type = (helloType)action_menu_item_get_action_data(action);
  
  // Play this vibration
  switch(s_current_type) {
    case spanishSpeak:  text_layer_set_text(s_voice_text, "Hola!");  break;
    case frenchSpeak:   text_layer_set_text(s_voice_text, "Bonjour!");   break;
    case germanSpeak: text_layer_set_text(s_voice_text, "Hallo!"); break;
    case finnishSpeak:   text_layer_set_text(s_voice_text, "Hei!");   break;
  }
}
static void voice_window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);
  window_set_background_color(s_voice_window, GColorFromRGB(96,223,229));
  
  s_background_layer = bitmap_layer_create(bounds);
  
  bitmap_layer_set_bitmap(s_background_layer, s_background_bitmap);
  layer_add_child(window_layer, bitmap_layer_get_layer(s_background_layer));
  
  s_voice_text = text_layer_create(GRect(0, 65, 144, 30));
  text_layer_set_text_color(s_voice_text, GColorBlack);
  text_layer_set_text(s_voice_text, displayText);
  text_layer_set_background_color(s_voice_text, GColorClear);
  text_layer_set_text_alignment(s_voice_text, GTextAlignmentCenter);
  text_layer_set_font(s_voice_text, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
  // Add to Window
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_voice_text));
   
  char *fuckme = "Hey!";
  char *fuckmehard = "Pushing IFTTT...";
  
  if(displayText == fuckme){
  action_menu = action_menu_level_create(4);

  action_menu_level_add_action(action_menu, "Spanish", hello_performed_callback, (void *)spanishSpeak);
  action_menu_level_add_action(action_menu, "French", hello_performed_callback, (void *)frenchSpeak);
  action_menu_level_add_action(action_menu, "German", hello_performed_callback, (void *)germanSpeak);
  action_menu_level_add_action(action_menu, "Finnish", hello_performed_callback, (void *)finnishSpeak);
  }
  if(displayText == fuckmehard){

  }
  }

static void voice_window_unload(Window *window) {
  text_layer_destroy(s_voice_text);
}

static void hello_select_callback(int index, void *ctx) {
  displayText = "Hey!";
  window_stack_push(s_voice_window, true);
}

static void IFTTT_select_callback(int index, void *ctx) {
  app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());
}

//Menu
static void menu_window_load(Window *window) {
  
  // Although we already defined NUM_FIRST_MENU_ITEMS, you can define
  // an int as such to easily change the order of menu items later
  int num_a_items = 0;

  s_first_menu_items[num_a_items++] = (SimpleMenuItem) {
    .title = "Hello",
    .subtitle = "Say hello!",
    .callback = hello_select_callback,
  };
  s_first_menu_items[num_a_items++] = (SimpleMenuItem) {
    .title = "What time is it?",
    .subtitle = "What time IS it??",
  //  .callback = menu_select_callback,
  };
  s_first_menu_items[num_a_items++] = (SimpleMenuItem) {
    .title = "Weather",
    .subtitle = "Is it hot in here?",
   // .callback = menu_select_callback,
    .icon = s_menu_icon_image,
  };
  s_first_menu_items[num_a_items++] = (SimpleMenuItem) {
    .title = "IFTTT",
    .subtitle = "Fire and IFTTT recipe",
    .callback = IFTTT_select_callback,
    .icon = s_menu_icon_image,
  };

  s_menu_sections[0] = (SimpleMenuSection) {
    .title = "Commands",
    .num_items = NUM_FIRST_MENU_ITEMS,
    .items = s_first_menu_items,
  };

  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_frame(window_layer);

  s_simple_menu_layer = simple_menu_layer_create(bounds, window, s_menu_sections, NUM_MENU_SECTIONS, NULL);

  layer_add_child(window_layer, simple_menu_layer_get_layer(s_simple_menu_layer));
  
}

static void menu_window_unload(Window *window) {
  simple_menu_layer_destroy(s_simple_menu_layer);
  }

