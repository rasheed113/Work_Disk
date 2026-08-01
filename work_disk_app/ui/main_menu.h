#ifndef MAIN_MENU_H
#define MAIN_MENU_H

namespace ui
{

class MainMenu
{
public:
    void show();

private:
    void displayMenu();
    void handleChoice(int choice);
};

} // namespace ui

#endif // MAIN_MENU_H