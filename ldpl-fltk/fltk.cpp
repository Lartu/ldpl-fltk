// --- Includes ---
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Round_Button.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Text_Editor.H>
#include <FL/Fl_Slider.H>
#include <FL/Fl_Value_Slider.H>
#include <FL/fl_ask.H>
#include <FL/Fl_File_Chooser.H>
using namespace std;


// --- Datatypes ---
class PWidget {
    public:
    Fl_Widget * widget;
    string str_value = "";
    bool isEntry = false;
    bool isMultiEntry = false;
    bool isWindow = false;
    bool isButton = false;
    bool isLabel = false;
    bool isSlider = false;
};


// --- Globals ---
unordered_map<string, PWidget> widgets;
ldpl_text LDPLFLTK_WIDGET_NAME;
ldpl_text LDPLFLTK_WIDGET_TEXT;
ldpl_text LDPLFLTK_WIDGET_TEXT2;
ldpl_text LDPLFLTK_WIDGET_TEXT3;
ldpl_text LDPLFLTK_WIDGET_TEXT4;
ldpl_text LDPLFLTK_WIDGET_TEXT5;
ldpl_number LDPLFLTK_N1;
ldpl_number LDPLFLTK_N2;
ldpl_number LDPLFLTK_N3;
ldpl_number LDPLFLTK_N4;


// --- External SUBs ---
void LDPLFLTK_CALLBACK();


// --- Theme Changing ---
void LDPLFLTK_THEME_FLTK()
{
    Fl::scheme("none");
}

void LDPLFLTK_THEME_GTK()
{
    Fl::scheme("gtk+");
}

void LDPLFLTK_THEME_PLASTIC()
{
    Fl::scheme("plastic");
}


// --- GUI Running ---
void LDPLFLTK_RUN()
{
    fl_message_icon()->hide();
    Fl::run();
}


// --- LDPL FLTK Internals ---
void add_widget(const string & name, PWidget & widget){
    widgets[name] = widget;
}

void error(string message)
{
    cout << "LDPL FLTK Error: " << message << endl;
    exit(1);
}

void warning(string message)
{
    cout << "LDPL FLTK Warning: " << message << endl;
    exit(1);
}

PWidget & get_widget(const string & name){
    auto widget = widgets.find(name);
    if (widget == widgets.end()){
        error("gui widget '" + name + "' doesn't exist.");
    }
    return widget->second;
}


// --- Callbacks ---
void button_pressed_callback(Fl_Widget * button, void * widget_name_data){
    LDPLFLTK_WIDGET_NAME = *((string *) widget_name_data);
    LDPLFLTK_WIDGET_TEXT = "pressed";
    LDPLFLTK_CALLBACK();
}

void entry_modified_callback(Fl_Widget * button, void * widget_name_data){
    LDPLFLTK_WIDGET_NAME = *((string *) widget_name_data);
    LDPLFLTK_WIDGET_TEXT = "modified";
    LDPLFLTK_CALLBACK();
}

void slider_modified_callback(Fl_Widget * button, void * widget_name_data){
    LDPLFLTK_WIDGET_NAME = *((string *) widget_name_data);
    LDPLFLTK_WIDGET_TEXT = "modified";
    LDPLFLTK_CALLBACK();
}


// --- FL_Widget Properties ---
void LDPLFLTK_SHOW()
{
    const string name = LDPLFLTK_WIDGET_NAME.str_rep();
    get_widget(name).widget->show();
}

void LDPLFLTK_LOCATE()
{
    const string name = LDPLFLTK_WIDGET_NAME.str_rep();
    ldpl_number y = LDPLFLTK_N2;
    ldpl_number x = LDPLFLTK_N1;
    get_widget(name).widget->position(x, y);
}

void LDPLFLTK_SIZE()
{
    const string name = LDPLFLTK_WIDGET_NAME.str_rep();
    ldpl_number h = LDPLFLTK_N2;
    ldpl_number w = LDPLFLTK_N1;
    get_widget(name).widget->size(w, h);
}

void LDPLFLTK_DISABLE()
{
    const string name = LDPLFLTK_WIDGET_NAME.str_rep();
    get_widget(name).widget->deactivate();
}

void LDPLFLTK_ENABLE()
{
    const string name = LDPLFLTK_WIDGET_NAME.str_rep();
    get_widget(name).widget->activate();
}

void LDPLFLTK_SETVALUE()
{
    const string name = LDPLFLTK_WIDGET_NAME.str_rep();
    ldpl_number value = LDPLFLTK_N1;
    PWidget & widget = get_widget(name);
    if (widget.isSlider)
    {
        ((Fl_Slider*)widget.widget)->value(value);
    }
    else
    {
        error("cannot set the value of a non-valued widget.");
    }
}

void LDPLFLTK_GETVALUE()
{
    const string name = LDPLFLTK_WIDGET_NAME.str_rep();
    PWidget & widget = get_widget(name);
    if (widget.isSlider)
    {
        LDPLFLTK_N2 = ((Fl_Slider*)widget.widget)->value();
    }
    else
    {
        error("cannot get the value of a non-valued widget.");
    }
}

void LDPLFLTK_SETTEXT()
{
    const string name = LDPLFLTK_WIDGET_NAME.str_rep();
    string value = LDPLFLTK_WIDGET_TEXT.str_rep();
    PWidget & widget = get_widget(name);
    if (widget.isEntry)
    {
        widget.str_value = value;
        ((Fl_Input_*)widget.widget)->value(widget.str_value.c_str());
    }
    else if (widget.isWindow)
    {
        widget.str_value = value;
        ((Fl_Window*)widget.widget)->label(widget.str_value.c_str());
    }
    else if (widget.isButton)
    {
        widget.str_value = value;
        ((Fl_Button*)widget.widget)->label(widget.str_value.c_str());
    }
    else if (widget.isMultiEntry)
    {
        widget.str_value = value;
        ((Fl_Text_Display*)widget.widget)->buffer()->text(widget.str_value.c_str());
    }
    else if (widget.isLabel || widget.isSlider)
    {
        widget.str_value = value;
        ((Fl_Widget*)widget.widget)->label(widget.str_value.c_str());
    }
    else
    {
        error("cannot set the text of a non-textual widget.");
    }
}

void LDPLFLTK_GETTEXT()
{
    const string name = LDPLFLTK_WIDGET_NAME.str_rep();
    PWidget & widget = get_widget(name);
    if (widget.isEntry)
    {
        LDPLFLTK_WIDGET_TEXT = ((Fl_Input*)widget.widget)->value();
    }
    else if (widget.isWindow)
    {
        LDPLFLTK_WIDGET_TEXT = ((Fl_Window*)widget.widget)->label();
    }
    else if (widget.isButton)
    {
        LDPLFLTK_WIDGET_TEXT = ((Fl_Button*)widget.widget)->label();
    }
    else if (widget.isMultiEntry)
    {
        LDPLFLTK_WIDGET_TEXT = ((Fl_Text_Display*)widget.widget)->buffer()->text();
    }
    else if (widget.isLabel || widget.isSlider)
    {
        LDPLFLTK_WIDGET_TEXT = ((Fl_Widget*)widget.widget)->label();
    }
    else
    {
        error("cannot get the text of a non-textual widget.");
    }
}

void LDPLFLTK_BOXED()
{
    const string name = LDPLFLTK_WIDGET_NAME.str_rep();
    get_widget(name).widget->box(FL_UP_BOX);
}


// --- Windows ---
void LDPLFLTK_OPEN_WINDOW()
{
    const string name = LDPLFLTK_WIDGET_NAME.str_rep();
    Fl_Window *window = new Fl_Window(550, 400, "LDPL FLTK");
    PWidget newWidget;
    newWidget.widget = window;
    newWidget.isWindow = true;
    add_widget(name, newWidget);
}

void LDPLFLTK_CLOSE_WINDOW()
{
    const string name = LDPLFLTK_WIDGET_NAME.str_rep();
    PWidget & widget = get_widget(name);
    if (widget.isWindow)
    {
        ((Fl_Window*)widget.widget)->end();
    }
    else
    {
        error("cannot end a non-container widget.");
    }
}

// --- Buttons ---
void LDPLFLTK_BUTTON()
{
    const string name = LDPLFLTK_WIDGET_NAME.str_rep();
    Fl_Button *button = new Fl_Button(0, 0, 100, 24, "Button");
    button->callback(button_pressed_callback, new string(name));
    PWidget newWidget;
    newWidget.widget = button;
    newWidget.isButton = true;
    add_widget(name, newWidget);
}

void LDPLFLTK_CHECK()
{
        const string name = LDPLFLTK_WIDGET_NAME.str_rep();
        Fl_Check_Button *button = new Fl_Check_Button(0, 0, 100, 24, "Check");
        button->callback(button_pressed_callback, new string(name));
        PWidget newWidget;
        newWidget.widget = button;
        newWidget.isButton = true;
        add_widget(name, newWidget);
}

void LDPLFLTK_RADIO()
{
        const string name = LDPLFLTK_WIDGET_NAME.str_rep();
        Fl_Round_Button *button = new Fl_Round_Button(0, 0, 100, 24, "Radio");
        button->callback(button_pressed_callback, new string(name));
        PWidget newWidget;
        newWidget.widget = button;
        newWidget.isButton = true;
        add_widget(name, newWidget);
}

// --- Entries ---
void LDPLFLTK_ENTRY()
{
    const string name = LDPLFLTK_WIDGET_NAME.str_rep();
    Fl_Input *entry = new Fl_Input(0, 0, 100, 24, "");
    entry->callback(entry_modified_callback, new string(name));
    PWidget newWidget;
    newWidget.widget = entry;
    newWidget.isEntry = true;
    add_widget(name, newWidget);
}

void LDPLFLTK_OUTPUT()
{
    const string name = LDPLFLTK_WIDGET_NAME.str_rep();
    Fl_Output *entry = new Fl_Output(0, 0, 100, 24, "");
    entry->callback(entry_modified_callback, new string(name));
    PWidget newWidget;
    newWidget.widget = entry;
    newWidget.isEntry = true;
    add_widget(name, newWidget);
}

void LDPLFLTK_TEXTENTRY()
{
    const string name = LDPLFLTK_WIDGET_NAME.str_rep();
    Fl_Text_Buffer *buff = new Fl_Text_Buffer();
    Fl_Text_Editor *entry = new Fl_Text_Editor(0, 0, 100, 24, "");
    entry->buffer(buff);
    entry->callback(entry_modified_callback, new string(name));
    entry->wrap_mode(1, 0);
    PWidget newWidget;
    newWidget.widget = entry;
    newWidget.isMultiEntry = true;
    add_widget(name, newWidget);
    //entry->linenumber_width(32);
}

void LDPLFLTK_TEXTOUTPUT()
{
    const string name = LDPLFLTK_WIDGET_NAME.str_rep();
    Fl_Text_Buffer *buff = new Fl_Text_Buffer();
    Fl_Text_Display *entry = new Fl_Text_Display(0, 0, 100, 24, "");
    entry->buffer(buff);
    entry->callback(entry_modified_callback, new string(name));
    entry->wrap_mode(1, 0);
    PWidget newWidget;
    newWidget.widget = entry;
    newWidget.isMultiEntry = true;
    add_widget(name, newWidget);
}

void LDPLFLTK_NOWRAP()
{
    const string name = LDPLFLTK_WIDGET_NAME.str_rep();
    PWidget & widget = get_widget(name);
    if (widget.isMultiEntry)
    {
        ((Fl_Text_Display*)widget.widget)->wrap_mode(0, 0);
    }
    else
    {
        warning("gui_nowrap can only be used with gui_textentry and gui_textoutput.");
    }
}

void LDPLFLTK_WRAP()
{
    const string name = LDPLFLTK_WIDGET_NAME.str_rep();
    PWidget & widget = get_widget(name);
    if (widget.isMultiEntry)
    {
        ((Fl_Text_Display*)widget.widget)->wrap_mode(1, 0);
    }
    else
    {
        warning("gui_nowrap can only be used with gui_textentry and gui_textoutput.");
    }
}

// --- Labels ---
void LDPLFLTK_LABEL()
{
    const string name = LDPLFLTK_WIDGET_NAME.str_rep();
    Fl_Box *box = new Fl_Box(0, 0, 100, 24, "");
    box->box(FL_NO_BOX);
    /*box->labelsize(20);*/
    box->align(FL_ALIGN_WRAP | FL_ALIGN_LEFT | FL_ALIGN_INSIDE);
    PWidget newWidget;
    newWidget.widget = box;
    newWidget.isLabel = true;
    add_widget(name, newWidget);
}

void LDPLFLTK_EMBOSS()
{
    const string name = LDPLFLTK_WIDGET_NAME.str_rep();
    PWidget & widget = get_widget(name);
    if (widget.isLabel)
    {
        widget.widget->labeltype(FL_EMBOSSED_LABEL);
    }else{
        warning("gui_emboss can only be used with gui_labels.");
    }
}

void LDPLFLTK_ITALIC()
{
    const string name = LDPLFLTK_WIDGET_NAME.str_rep();
    PWidget & widget = get_widget(name);
    if (widget.isLabel)
    {
        widget.widget->labelfont(FL_ITALIC);
    }else{
        warning("gui_italic can only be used with gui_labels.");
    }
}

void LDPLFLTK_BOLD()
{
    const string name = LDPLFLTK_WIDGET_NAME.str_rep();
    PWidget & widget = get_widget(name);
    if (widget.isLabel)
    {
        widget.widget->labelfont(FL_BOLD);
    }else{
        warning("gui_bold can only be used with gui_labels.");
    }
}

void LDPLFLTK_BOLDITALIC()
{
    const string name = LDPLFLTK_WIDGET_NAME.str_rep();
    PWidget & widget = get_widget(name);
    if (widget.isLabel)
    {
        widget.widget->labelfont(FL_ITALIC|FL_BOLD);
    }else{
        warning("gui_bolditalic can only be used with gui_labels.");
    }
}

void LDPLFLTK_SHADOW()
{
    const string name = LDPLFLTK_WIDGET_NAME.str_rep();
    PWidget & widget = get_widget(name);
    if (widget.isLabel)
    {
        widget.widget->labeltype(FL_SHADOW_LABEL);
    }else{
        warning("gui_shadow can only be used with gui_labels.");
    }
}

void LDPLFLTK_CENTER()
{
    const string name = LDPLFLTK_WIDGET_NAME.str_rep();
    PWidget & widget = get_widget(name);
    if (widget.isLabel){
        widget.widget->align(FL_ALIGN_WRAP | FL_ALIGN_CENTER | FL_ALIGN_INSIDE);
    }else{
        warning("gui_center can only be used with gui_labels.");
    }
}

void LDPLFLTK_LEFT()
{
    const string name = LDPLFLTK_WIDGET_NAME.str_rep();
    PWidget & widget = get_widget(name);
    if (widget.isLabel){
        widget.widget->align(FL_ALIGN_WRAP | FL_ALIGN_LEFT | FL_ALIGN_INSIDE);
    }else{
        warning("gui_left can only be used with gui_labels.");
    }
}

void LDPLFLTK_RIGHT()
{
    const string name = LDPLFLTK_WIDGET_NAME.str_rep();
    PWidget & widget = get_widget(name);
    if (widget.isLabel){
        widget.widget->align(FL_ALIGN_WRAP | FL_ALIGN_RIGHT | FL_ALIGN_INSIDE);
    }else{
        warning("gui_right can only be used with gui_labels.");
    }
}


// --- Sliders ---
void LDPLFLTK_SLIDER()
{
    const string name = LDPLFLTK_WIDGET_NAME.str_rep();
    Fl_Slider * roller = new Fl_Slider(0, 0, 100, 24, "");
    roller->callback(slider_modified_callback, new string(name));
    roller->type(FL_HORIZONTAL);
    roller->value(0);
    roller->labelsize(10);
    PWidget newWidget;
    newWidget.widget = roller;
    newWidget.isSlider = true;
    add_widget(name, newWidget);
}

void LDPLFLTK_VSLIDER()
{
    const string name = LDPLFLTK_WIDGET_NAME.str_rep();
    Fl_Slider * roller = new Fl_Slider(0, 0, 24, 100, "");
    roller->callback(slider_modified_callback, new string(name));
    roller->type(FL_VERTICAL);
    roller->value(0);
    roller->labelsize(10);
    PWidget newWidget;
    newWidget.widget = roller;
    newWidget.isSlider = true;
    add_widget(name, newWidget);
}

void LDPLFLTK_FILLSLIDER()
{
    const string name = LDPLFLTK_WIDGET_NAME.str_rep();
    Fl_Slider * roller = new Fl_Slider(0, 0, 24, 100, "");
    roller->callback(slider_modified_callback, new string(name));
    roller->type(FL_HOR_FILL_SLIDER);
    roller->color2(0x1c82e800); 
    roller->value(0);
    roller->labelsize(10);
    PWidget newWidget;
    newWidget.widget = roller;
    newWidget.isSlider = true;
    add_widget(name, newWidget);
}

void LDPLFLTK_VFILLSLIDER()
{
    const string name = LDPLFLTK_WIDGET_NAME.str_rep();
    Fl_Slider * roller = new Fl_Slider(0, 0, 24, 100, "");
    roller->callback(slider_modified_callback, new string(name));
    roller->type(FL_VERT_FILL_SLIDER);
    roller->color2(0x1c82e800); 
    roller->value(0);
    roller->labelsize(10);
    PWidget newWidget;
    newWidget.widget = roller;
    newWidget.isSlider = true;
    add_widget(name, newWidget);
}

void LDPLFLTK_VALUESLIDER()
{
    const string name = LDPLFLTK_WIDGET_NAME.str_rep();
    Fl_Value_Slider * roller = new Fl_Value_Slider(0, 0, 24, 100, "");
    roller->callback(slider_modified_callback, new string(name));
    roller->type(FL_HOR_FILL_SLIDER);
    roller->color2(0x1c82e800); 
    roller->value(0);
    roller->labelsize(10);
    PWidget newWidget;
    newWidget.widget = roller;
    newWidget.isSlider = true;
    add_widget(name, newWidget);
}

void LDPLFLTK_VVALUESLIDER()
{
    const string name = LDPLFLTK_WIDGET_NAME.str_rep();
    Fl_Value_Slider * roller = new Fl_Value_Slider(0, 0, 24, 100, "");
    roller->callback(slider_modified_callback, new string(name));
    roller->type(FL_VERT_FILL_SLIDER);
    roller->color2(0x1c82e800); 
    roller->value(0);
    roller->labelsize(10);
    PWidget newWidget;
    newWidget.widget = roller;
    newWidget.isSlider = true;
    add_widget(name, newWidget);
}

void LDPLFLTK_VALUEFILLSLIDER()
{
    const string name = LDPLFLTK_WIDGET_NAME.str_rep();
    Fl_Value_Slider * roller = new Fl_Value_Slider(0, 0, 24, 100, "");
    roller->callback(slider_modified_callback, new string(name));
    roller->type(FL_HOR_FILL_SLIDER);
    roller->color2(0x1c82e800); 
    roller->value(0);
    roller->labelsize(10);
    PWidget newWidget;
    newWidget.widget = roller;
    newWidget.isSlider = true;
    add_widget(name, newWidget);
}

void LDPLFLTK_VVALUEFILLSLIDER()
{
    const string name = LDPLFLTK_WIDGET_NAME.str_rep();
    Fl_Value_Slider * roller = new Fl_Value_Slider(0, 0, 24, 100, "");
    roller->callback(slider_modified_callback, new string(name));
    roller->type(FL_VERT_FILL_SLIDER);
    roller->color2(0x1c82e800); 
    roller->value(0);
    roller->labelsize(10);
    PWidget newWidget;
    newWidget.widget = roller;
    newWidget.isSlider = true;
    add_widget(name, newWidget);
}

void LDPLFLTK_SLIDERBOUNDS()
{
    const string name = LDPLFLTK_WIDGET_NAME.str_rep();
    ldpl_number min = LDPLFLTK_N1;
    ldpl_number max = LDPLFLTK_N2;
    ldpl_number step = LDPLFLTK_N3;
    PWidget & widget = get_widget(name);
    if (widget.isSlider)
    {
        ((Fl_Slider*)widget.widget)->minimum(min);
        ((Fl_Slider*)widget.widget)->maximum(max);
        ((Fl_Slider*)widget.widget)->step(step);
        ((Fl_Slider*)widget.widget)->value(min);
    }else{
        warning("gui_sliderbounds can only be used with gui_sliders.");
    }
}

// --- Dialogs ---
void LDPLFLTK_MESSAGE()
{
    string title = LDPLFLTK_WIDGET_TEXT.str_rep();
    string message = LDPLFLTK_WIDGET_TEXT2.str_rep();
    fl_message_title(title.c_str());
    fl_message("%s", message.c_str());
}

void LDPLFLTK_QUESTION()
{
    string title = LDPLFLTK_WIDGET_TEXT.str_rep();
    string message = LDPLFLTK_WIDGET_TEXT2.str_rep();
    string opt3 = LDPLFLTK_WIDGET_TEXT5.str_rep();
    string opt2 = LDPLFLTK_WIDGET_TEXT4.str_rep();
    string opt1 = LDPLFLTK_WIDGET_TEXT3.str_rep();
    fl_message_title(title.c_str());
    int res = fl_choice("%s"
        , opt1 != "" ? opt1.c_str() : (char *) 0
        , opt2 != "" ? opt2.c_str() : (char *) 0 //Default
        , opt3 != "" ? opt3.c_str() : (char *) 0
        , message.c_str());
    LDPLFLTK_N1 = res;
}

void LDPLFLTK_FILEDIALOG()
{
    //TODO add type
    string homeDir = exec("echo $HOME").str_rep();
    string pathname = ".";
    string title = LDPLFLTK_WIDGET_TEXT2.str_rep().c_str();
    string type = LDPLFLTK_WIDGET_TEXT.str_rep();
    char * result;
    if(type == "file")
    {
        result = fl_file_chooser(title.c_str(), "*", pathname.c_str(), 1);
    }
    else if(type == "dir")
    {
        result = fl_dir_chooser(title.c_str(), pathname.c_str(), 1);
    }
    else
    {
    error("unknown file selection type: '" + type + "'");
    }
    if (result != NULL){
        LDPLFLTK_WIDGET_TEXT3 = result;
    }else{
        LDPLFLTK_WIDGET_TEXT = "";
    }
}


