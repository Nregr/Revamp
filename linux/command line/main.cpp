#include "operations.h"
#include "arguments.h"
#include "colors.h"
#include <sys/utsname.h>
#include <unistd.h>
#include <string.h>

#define maxLimit 2000

using namespace std;

string getOsn()
{
    FILE *ptr = fopen("/etc/os-release", "r");
    char str[maxLimit], ch;
    string osn = "revamp";
    while(fscanf(ptr, "%[^\n]s", str) != -1){
        if(str[0] == 'I' && str[1] == 'D')
        {
            osn = string(&str[3]);
            return osn;
        }
        fscanf(ptr, "%c", &ch);
    }
    return osn;
}

void printText(string str, string colorName)                    //fancy display
{
    string print = "\033[38;5;" + to_string(get_color(colorName)) + "m";    //ANSI Escape...
    print += str;
    print += "\033[0m";
    cout << print;
}

void disp(char *user)
{
    char cwd[maxLimit];
    string osn = getOsn();
    getlogin_r(user, maxLimit);
    getcwd(cwd, maxLimit);
    printText("\u250C\u2500[", "red");
    printText(user, "black");
    printText("@", "yellow");
    printText(osn, "blue");
    printText("\u2500[~", "red");
    printText(cwd, "green");
    printText("]\n\u2514\u2500\u2500\u2578", "red");
    printText("$", "yellow");
}

int main(int narg, char *arg[])
{
    if(narg > 1)                                                     //Process arguments if provided
    {
        handle_args(narg, arg);
        return 0;
    }
    cout << "---------------Revamp---------------\n\n";
    char command[maxLimit], buff, user[maxLimit];
    while (true)
    {
        disp(user);
        scanf("%[^\n]s", command);
        scanf("%c", &buff);
        if(strcmp(command, "exit") == 0)
        {
            cout << "Bye, Have a good day " << user << ".\n";
            return 0;
        }
        std::system(command);
    }
    return 0;
}
