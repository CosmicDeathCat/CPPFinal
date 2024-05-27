#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;

enum en_DIRS {NORTH, EAST, SOUTH, WEST};
enum en_ROOMS {SOUTH_MAIN_ROAD, TAVERN, ANCIENT_TREESTUMP, ADVENTURERS_GUILD, FORGE, GLOWING_POND, WINE_CELLAR, STABLES, PATH_OUT_OF_TOWN, BRIDGE, PASTURE, SIDE_ROAD, TOWN_HALL, FOUNDERS_STATUE, NORTH_MAIN_ROAD, BAKERY, FORGOTTEN_PATH, GRAVEYARD, ABANDONED_HOUSE, OVERGROWN_GARDEN, VILLAGERS_HOUSES, SMALL_VILLAGE_GARDEN, MAYORS_HOME, BROKEN_FOUNTAIN, SHOPPING_CENTER, APOTHECARY, WIZARD_TOWER};
enum en_VERBS {GET, DROP, USE, OPEN, CLOSE, EXAMINE, INVENTORY, LOOK, SEARCH,EXCHANGE, CHEST, TALK, OBSERVE, LISTEN, JOURNAL};
enum en_NOUNS {CELLAR_DOOR, OLD_COIN, EMPTY_ALE_BOTTLE, BASKET_OF_EGGS, DOG_BONE, NEWS_PAPER, LOST_RING, WATERING_CAN, COIN_PURSE, LOVE_POTION, FLYER, CHEESE_WHEEL, RUBY, DAGGER, COCONUT_PIECES, GLOWING_STONE, TINY_CROWN, MYSTERIOUS_KEY, MAGICAL_RELIC, LUNCH_BOX};

const int NONE = -1;
const int DIRS = 4;
const int ROOMS = 27;
const int VERBS = 15;
const int NOUNS = 20;
bool winGame = false;
int villagerFavorPoints = 0;

class Room {
public:
    string description;
    int exits[DIRS];
    bool visited;

    Room() {}
    
    Room(const string& desc) : description(desc) {
        for (int i = 0; i < DIRS; ++i) {
            exits[i] = NONE;
        }
    }
    ~Room()
    {
    }
};

class Noun {
public:
    string word; 
    string description;
    int code;
    int location;
    bool canCarry;
    bool canBeFound;

    Noun() {}
    
    Noun(const string& word_, const string& desc, int code_, int location_ = NONE, bool canCarry_ = false, bool canBeFound_ = true)
        : word(word_), description(desc), code(code_), location(location_), canCarry(canCarry_), canBeFound(canBeFound_) {}
    ~Noun()
    {
    }
};

class Word {
public:
    string str;
    int code;

    Word() {}

    Word(const string& str_, const int& code_)
        :str(str_), code(code_){}
    ~Word()
    {
    }
};

void set_rooms(vector<Room>& rooms)
{
    rooms.resize(ROOMS);
    rooms[SOUTH_MAIN_ROAD] = Room("southern part of the main road of the village");
    rooms[SOUTH_MAIN_ROAD].exits[NORTH] = NORTH_MAIN_ROAD;
    rooms[SOUTH_MAIN_ROAD].exits[EAST] = TAVERN;
    rooms[SOUTH_MAIN_ROAD].exits[SOUTH] = SIDE_ROAD;
    rooms[SOUTH_MAIN_ROAD].exits[WEST] = ADVENTURERS_GUILD;

    rooms[TAVERN] = Room("The Tavern. Loud tavern with a bar, and rooms for rent.\nThere seems to be lost of empty bottles behind the bar in a basket.");
    rooms[TAVERN].exits[NORTH] = SHOPPING_CENTER;
    rooms[TAVERN].exits[EAST] = NONE;
    rooms[TAVERN].exits[SOUTH] = NONE;
    rooms[TAVERN].exits[WEST] = SOUTH_MAIN_ROAD;

    rooms[ANCIENT_TREESTUMP] = Room("The forgotten ancient treestump.\nThis old stump once was the home of the fae.\nThere appear to be small footprints around it.");
    rooms[ANCIENT_TREESTUMP].exits[NORTH] = NONE;
    rooms[ANCIENT_TREESTUMP].exits[EAST] = NORTH_MAIN_ROAD;
    rooms[ANCIENT_TREESTUMP].exits[SOUTH] = ADVENTURERS_GUILD;
    rooms[ANCIENT_TREESTUMP].exits[WEST] = NONE;

    rooms[ADVENTURERS_GUILD] = Room("The local adventurers guild.\nA place for adventurers to gather, drink, and rest.\nThere is a large orc at the front desk and behind him is a bulletin board.");
    rooms[ADVENTURERS_GUILD].exits[NORTH] = ANCIENT_TREESTUMP;
    rooms[ADVENTURERS_GUILD].exits[EAST] = SOUTH_MAIN_ROAD;
    rooms[ADVENTURERS_GUILD].exits[SOUTH] = NONE;
    rooms[ADVENTURERS_GUILD].exits[WEST] = NONE;

    rooms[FORGE] = Room("Dwarven forge with a few beautifully crafted swords on display.\nThe blacksmith seems to be upset about losing a tool, and his wife is making jewelery.");
    rooms[FORGE].exits[NORTH] = NONE;
    rooms[FORGE].exits[EAST] = NONE;
    rooms[FORGE].exits[SOUTH] = NONE;
    rooms[FORGE].exits[WEST] = SHOPPING_CENTER;

    rooms[GLOWING_POND] = Room("The beautiful glowing pond.\nThe pond here emits a mysterious glow.\nIt's in the center of new village.\nThere is a huge willow tree next to it.");
    rooms[GLOWING_POND].exits[NORTH] = BRIDGE;
    rooms[GLOWING_POND].exits[EAST] = WINE_CELLAR;
    rooms[GLOWING_POND].exits[SOUTH] = NORTH_MAIN_ROAD;
    rooms[GLOWING_POND].exits[WEST] = VILLAGERS_HOUSES;

    rooms[WINE_CELLAR] = Room("hidden wine cellar by the pond.\nIt is partially covered by bushes.\nIs it still in use?");
    rooms[WINE_CELLAR].exits[NORTH] = NONE;
    rooms[WINE_CELLAR].exits[EAST] = NONE;
    rooms[WINE_CELLAR].exits[SOUTH] = NONE;
    rooms[WINE_CELLAR].exits[WEST] = NONE;

    rooms[STABLES] = Room("The stables.\nMany horses are kept here.\nThe smell of hay and manure is strong.\nThe horses seem to be enjoying some fruit.");
    rooms[STABLES].exits[NORTH] = PASTURE;
    rooms[STABLES].exits[EAST] = VILLAGERS_HOUSES;
    rooms[STABLES].exits[SOUTH] = NONE;
    rooms[STABLES].exits[WEST] = NONE;

    rooms[PATH_OUT_OF_TOWN] = Room("The path out of town.\nA path leading out of town.\nIt looks a bit rough.\nThere is a directional sign that has directions everywhere but to the east which has been scratched out.");
    rooms[PATH_OUT_OF_TOWN].exits[NORTH] = NONE;
    rooms[PATH_OUT_OF_TOWN].exits[EAST] = FORGOTTEN_PATH;
    rooms[PATH_OUT_OF_TOWN].exits[SOUTH] = BRIDGE;
    rooms[PATH_OUT_OF_TOWN].exits[WEST] = WIZARD_TOWER;

    rooms[BRIDGE] = Room("The bridge going out of town.\nA stone bridge that leads to the path out of town.\nIt looks newly built.\nThe river below is full of fish.");
    rooms[BRIDGE].exits[NORTH] = PATH_OUT_OF_TOWN;
    rooms[BRIDGE].exits[EAST] = NONE;
    rooms[BRIDGE].exits[SOUTH] = GLOWING_POND;
    rooms[BRIDGE].exits[WEST] = NONE;

    rooms[PASTURE] = Room("peaceful pasture which adventurers horses come to graze.\nThe horses seem to be at happy here. ");
    rooms[PASTURE].exits[NORTH] = NONE;
    rooms[PASTURE].exits[EAST] = NONE;
    rooms[PASTURE].exits[SOUTH] = STABLES;
    rooms[PASTURE].exits[WEST] = NONE;

    rooms[SIDE_ROAD] = Room("Small road off of the main road.\nA small side road that leads to the important places in town.\nIt's a bit quieter here.\nThe road is a bit rough.");
    rooms[SIDE_ROAD].exits[NORTH] = SOUTH_MAIN_ROAD;
    rooms[SIDE_ROAD].exits[EAST] = FOUNDERS_STATUE;
    rooms[SIDE_ROAD].exits[SOUTH] = TOWN_HALL;
    rooms[SIDE_ROAD].exits[WEST] = BAKERY;

    rooms[TOWN_HALL] = Room("great town hall.\nThe place where the mayor and council meet.\nIt has a guardian statue in front it looks like a dragon.\nInside there is a small museum.");
    rooms[TOWN_HALL].exits[NORTH] = SIDE_ROAD;
    rooms[TOWN_HALL].exits[EAST] = NONE;
    rooms[TOWN_HALL].exits[SOUTH] = NONE;
    rooms[TOWN_HALL].exits[WEST] = NONE;

    rooms[FOUNDERS_STATUE] = Room("founder's statue.\nA statue of the mayors great grandfather who took the village away from the fae with the help of his pet dragon.");
    rooms[FOUNDERS_STATUE].exits[NORTH] = MAYORS_HOME;
    rooms[FOUNDERS_STATUE].exits[EAST] = NONE;
    rooms[FOUNDERS_STATUE].exits[SOUTH] = NONE;
    rooms[FOUNDERS_STATUE].exits[WEST] = SIDE_ROAD;

    rooms[MAYORS_HOME] = Room("mayors home.\nIt's a large house compared to the others in the village.\nThe mayor seems to be distraught about something.");
    rooms[MAYORS_HOME].exits[NORTH] = NONE;
    rooms[MAYORS_HOME].exits[EAST] = NONE;
    rooms[MAYORS_HOME].exits[SOUTH] = FOUNDERS_STATUE;
    rooms[MAYORS_HOME].exits[WEST] = NONE;

    rooms[NORTH_MAIN_ROAD] = Room("northern main road of the village.");
    rooms[NORTH_MAIN_ROAD].exits[NORTH] = GLOWING_POND;
    rooms[NORTH_MAIN_ROAD].exits[EAST] = SHOPPING_CENTER;
    rooms[NORTH_MAIN_ROAD].exits[SOUTH] = SOUTH_MAIN_ROAD;
    rooms[NORTH_MAIN_ROAD].exits[WEST] = ANCIENT_TREESTUMP;

    rooms[BAKERY] = Room("popular bakery.\nThis bakery is known throughout the kingdom for exceptional pastries.\nMany adventurers come to learn how to bake.\nThe smell of fresh bread fills the air.");
    rooms[BAKERY].exits[NORTH] = NONE;
    rooms[BAKERY].exits[EAST] = SIDE_ROAD;
    rooms[BAKERY].exits[SOUTH] = NONE;
    rooms[BAKERY].exits[WEST] = NONE;

    rooms[FORGOTTEN_PATH] = Room("forgotten path.\nIt's easy to miss this path.\nIt's overgrown and has an eerie feel to it.\nThere seems to be a magical presence here.");
    rooms[FORGOTTEN_PATH].exits[NORTH] = NONE;
    rooms[FORGOTTEN_PATH].exits[EAST] = GRAVEYARD;
    rooms[FORGOTTEN_PATH].exits[SOUTH] = ABANDONED_HOUSE;
    rooms[FORGOTTEN_PATH].exits[WEST] = PATH_OUT_OF_TOWN;

    rooms[GRAVEYARD] = Room("The rumored to be haunted graveyard.\nOnly the most important people are buried here. \nThe mayor's family has a large mausoleum here.\nThere is a gravekeeper who is always working.");
    rooms[GRAVEYARD].exits[NORTH] = NONE;
    rooms[GRAVEYARD].exits[EAST] = NONE;
    rooms[GRAVEYARD].exits[SOUTH] = NONE;
    rooms[GRAVEYARD].exits[WEST] = FORGOTTEN_PATH;

    rooms[ABANDONED_HOUSE] = Room("abandoned house.\nThis house is rumored to have been inhabited by a witch that helped the fae.\nNow it's rickety and falling apart.\nYou think you might have seen a small light, but it's probably your imagination.");
    rooms[ABANDONED_HOUSE].exits[NORTH] = FORGOTTEN_PATH;
    rooms[ABANDONED_HOUSE].exits[EAST] = NONE;
    rooms[ABANDONED_HOUSE].exits[SOUTH] = OVERGROWN_GARDEN;
    rooms[ABANDONED_HOUSE].exits[WEST] = NONE;

    rooms[OVERGROWN_GARDEN] = Room("garden behind the house.\nYou think this might have been a wonderful garden at one point.\nThere are many flowers and herbs growing here despite it being abandoned.\nYou hear the sound of a fountain nearby.");
    rooms[OVERGROWN_GARDEN].exits[NORTH] = ABANDONED_HOUSE;
    rooms[OVERGROWN_GARDEN].exits[EAST] = BROKEN_FOUNTAIN;
    rooms[OVERGROWN_GARDEN].exits[SOUTH] = NONE;
    rooms[OVERGROWN_GARDEN].exits[WEST] = NONE;

    rooms[VILLAGERS_HOUSES] = Room("neighborhood which the villagers live.\nThere are many beautiful houses made of stone and wood.\nThe building style is tudor.\nThe villagers seem to be friendly.\nYou see some beggars near the road.");
    rooms[VILLAGERS_HOUSES].exits[NORTH] = SMALL_VILLAGE_GARDEN;
    rooms[VILLAGERS_HOUSES].exits[EAST] = GLOWING_POND;
    rooms[VILLAGERS_HOUSES].exits[SOUTH] = NONE;
    rooms[VILLAGERS_HOUSES].exits[WEST] = STABLES;

    rooms[SMALL_VILLAGE_GARDEN] = Room("small garden to the north of the neighborhood.\nA small community garden where villagers grow many varieties of vegetables and herbs to share with their community.\nThere is an old dog who waits for treats.");
    rooms[SMALL_VILLAGE_GARDEN].exits[NORTH] = NONE;
    rooms[SMALL_VILLAGE_GARDEN].exits[EAST] = NONE;
    rooms[SMALL_VILLAGE_GARDEN].exits[SOUTH] = VILLAGERS_HOUSES;
    rooms[SMALL_VILLAGE_GARDEN].exits[WEST] = NONE;

    rooms[BROKEN_FOUNTAIN] = Room("broken fountain.\nThis fountain is broken and has been for a long time.\nIt's beautifully crafted and has a small plaque that reads 'Always remember the fae'.\nThere are runes on the base of the fountain.");
    rooms[BROKEN_FOUNTAIN].exits[NORTH] = NONE;
    rooms[BROKEN_FOUNTAIN].exits[EAST] = NONE;
    rooms[BROKEN_FOUNTAIN].exits[SOUTH] = NONE;
    rooms[BROKEN_FOUNTAIN].exits[WEST] = OVERGROWN_GARDEN;

    rooms[SHOPPING_CENTER] = Room("busy shopping center.\nA large area where there are many shop stalls with the sounds of people haggling and the smells of many foods.\nThere are stalls for many things here.\nMany villagers are here shopping.");
    rooms[SHOPPING_CENTER].exits[NORTH] = APOTHECARY;
    rooms[SHOPPING_CENTER].exits[EAST] = FORGE;
    rooms[SHOPPING_CENTER].exits[SOUTH] = TAVERN;
    rooms[SHOPPING_CENTER].exits[WEST] = NORTH_MAIN_ROAD;

    rooms[APOTHECARY] = Room("Black Cat Apothecary.\nA small shop with potions and herbs that are said to have magical properties.\nThe shopkeeper is a very mysterious elf.");
    rooms[APOTHECARY].exits[NORTH] = NONE;
    rooms[APOTHECARY].exits[EAST] = NONE;
    rooms[APOTHECARY].exits[SOUTH] = SHOPPING_CENTER;
    rooms[APOTHECARY].exits[WEST] = NONE;

    rooms[WIZARD_TOWER] = Room("The wizard's tower.\nA tall tower that is said to be the oldest building in the village.\nThe wizard is highly respected and protects the village from magical threats.");
    rooms[WIZARD_TOWER].exits[NORTH] = NONE;
    rooms[WIZARD_TOWER].exits[EAST] = PATH_OUT_OF_TOWN;
    rooms[WIZARD_TOWER].exits[SOUTH] = NONE;
    rooms[WIZARD_TOWER].exits[WEST] = NONE;
    
}

void set_directions(vector<Word>& dir)
{
    dir.resize(DIRS);
    dir[NORTH].str.assign("NORTH");
    dir[NORTH].code = NORTH;
    dir[EAST].str.assign("EAST");
    dir[EAST].code = EAST;
    dir[SOUTH].str.assign("SOUTH");
    dir[SOUTH].code = SOUTH;
    dir[WEST].str.assign("WEST");
    dir[WEST].code = WEST;
}

void set_verbs(vector<Word>& vbs)
{
    vbs.resize(VERBS);
    vbs[GET].str.assign("GET");
    vbs[GET].code = GET;
    vbs[DROP].str.assign("DROP");
    vbs[DROP].code = DROP;
    vbs[USE].str.assign("USE");
    vbs[USE].code = USE;
    vbs[OPEN].str.assign("OPEN");
    vbs[OPEN].code = OPEN;
    vbs[CLOSE].str.assign("CLOSE");
    vbs[CLOSE].code = CLOSE;
    vbs[EXAMINE].str.assign("EXAMINE");
    vbs[EXAMINE].code = EXAMINE;
    vbs[INVENTORY].str.assign("INVENTORY");
    vbs[INVENTORY].code = INVENTORY;
    vbs[LOOK].str.assign("LOOK");
    vbs[LOOK].code = LOOK;
    vbs[SEARCH].str.assign("SEARCH");
    vbs[SEARCH].code = SEARCH;
    vbs[EXCHANGE].str.assign("EXCHANGE");
    vbs[EXCHANGE].code = EXCHANGE;
    vbs[CHEST].str.assign("CHEST");
    vbs[CHEST].code = CHEST;
    vbs[TALK].str.assign("TALK");
    vbs[TALK].code = TALK;
    vbs[OBSERVE].str.assign("OBSERVE");
    vbs[OBSERVE].code = OBSERVE;
    vbs[LISTEN].str.assign("LISTEN");
    vbs[LISTEN].code = LISTEN;
    vbs[JOURNAL].str.assign("JOURNAL");
    vbs[JOURNAL].code = JOURNAL;
}

void set_nouns(vector<Noun>& nouns)
{
    nouns.resize(NOUNS);
    nouns[CELLAR_DOOR] = Noun("Cellar DOOR", "A mysterious moss covered door.", CELLAR_DOOR, WINE_CELLAR, false);
    nouns[OLD_COIN] = Noun("OLD COIN", "an old coin looks like it's from the fae era.", OLD_COIN, NONE, true);
    nouns[EMPTY_ALE_BOTTLE] = Noun("EMPTY ALE BOTTLE", "Looks like it was left here recently.\nLittering is bad.", EMPTY_ALE_BOTTLE, NONE, true);
    nouns[BASKET_OF_EGGS] = Noun("BASKET OF EGGS", "Someone must have forgotten these.\nThey look fresh.", BASKET_OF_EGGS, NONE, true);
    nouns[DOG_BONE] = Noun("DOG BONE", "A dog must had hidden this here.\nIt's a bit chewed up.", DOG_BONE, NONE,  true);
    nouns[NEWS_PAPER] = Noun("NEWS PAPER", "A newspaper with the headline 'Mayor's approval rating at an all time high despite the scandal'.", NEWS_PAPER, NONE, true);
    nouns[LOST_RING] = Noun("LOST RING", "Looks like it is a wedding ring.\nI hope the owner finds it.",  LOST_RING, NONE, true);
    nouns[WATERING_CAN] = Noun("WATERING CAN", "This watering can looks like it's been used a lot.", WATERING_CAN, NONE, true);
    nouns[COIN_PURSE] = Noun("COIN PURSE", "An emerald green coin purse.\nIt's empty.", COIN_PURSE, NONE, true);
    nouns[LOVE_POTION] = Noun("LOVE POTION", "A small vial with a rose colored liquid.\nLooks like someone changed their mind.", LOVE_POTION, NONE, true);
    nouns[FLYER] = Noun("FLYER", "A flyer from the adventurers guild.\nIt shows a quest to clear out the goblins in the forest.", FLYER, NONE, true);
    nouns[CHEESE_WHEEL] = Noun("CHEESE WHEEL", "You are not entirely sure how this got here, or why it is here.\nIt has a slice missing, and small crumbs trailing from the missing piece.", CHEESE_WHEEL, NONE, true);
    nouns[RUBY] = Noun("RUBY", "A small ruby, it might have been part of a necklace, ring, or came from a vase.", RUBY, NONE, true);
    nouns[DAGGER] = Noun("DAGGER", "A small dagger it looks like it was hidden here.\nIt's sharp.", DAGGER, NONE, true);
    nouns[COCONUT_PIECES] = Noun("COCONUT PIECES", "What are these doing out of the stables!", COCONUT_PIECES, NONE, true);
    nouns[GLOWING_STONE] = Noun("GLOWING STONE", "A small stone that glows. It's warm to the touch.", GLOWING_STONE, NONE, true);
    nouns[TINY_CROWN] = Noun("TINY CROWN", "A small crown that looks doesn't even look real.\nIt looks like it was made for a doll.", TINY_CROWN, NONE, true);
    nouns[MYSTERIOUS_KEY] = Noun("MYSTERIOUS KEY", "A key that looks very old. It might be for something important.", MYSTERIOUS_KEY, NONE, true);
    nouns[MAGICAL_RELIC] = Noun("MAGICAL RELIC", "A small relic that looks like it was part of a larger piece.", MAGICAL_RELIC, NONE, true);
    nouns[LUNCH_BOX] = Noun("LUNCH BOX", "A lunch box full of food that is still warm.", LUNCH_BOX, NONE, true);
    
    
}

void randomItemLocations(vector<Noun>& nouns) {
    vector<int> roomIndices;
    for (int i = 0; i < ROOMS; i++) {
        roomIndices.push_back(i);
    }
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    shuffle(roomIndices.begin(), roomIndices.end(), default_random_engine(seed));

    int roomIndex = 0; 
    for (int i = 0; i < NOUNS; i++) {
        if (nouns[i].location == NONE) {
            nouns[i].location = roomIndices[roomIndex];
            roomIndex++; 
        }
    }
}

void section_command(string Cmd, string &wd1, string &wd2)
{
    string sub_str;
    vector<string> words;
    char search = ' ';
    size_t i, j;

    for(i = 0; i < Cmd.size(); i++)
    {
        if(Cmd.at(i) != search)
        {
            sub_str.insert(sub_str.end(), Cmd.at(i));
        }
        if(i == Cmd.size() - 1)
        {
            words.push_back(sub_str);
            sub_str.clear();
        }
        if(Cmd.at(i) == search)
        {
            words.push_back(sub_str);
            sub_str.clear();
        }
    }

    for(i = words.size() - 1; i > 0; i--)
    {
        if(words.at(i) == "")
        {
            words.erase(words.begin() + i);
        }
    }

    for(i = 0; i < words.size(); i++)
    {
        for(j = 0; j < words.at(i).size(); j++)
        {
            if(islower(words.at(i).at(j)))
            {
                words.at(i).at(j) = toupper(words.at(i).at(j));
            }
        }
    }
    if (words.size() == 0) {
    } else if (words.size() == 1) {
        wd1 = words.at(0);
    } else {
        wd1 = words.at(0);

        for (int i = 1; i < words.size(); i++) {
            wd2 += words[i];
            if (i < words.size() - 1) { 
                wd2 += " ";
            } 
        }
    } 
}

void look_around(int loc, const vector<Room>& rooms, const vector<Word>& dirs) {
    cout << "I am in the " << rooms[loc].description << ".\n";

    for (int i = 0; i < DIRS; ++i) {
        if (rooms[loc].exits[i] != NONE) {
            cout << "Exits are to the: " << dirs[i].str << '\n';
        }
    }
}

void inventory (std::vector<Noun>& nouns)
{
    cout << "You are carrying: \n";
    for (int i = 0; i < nouns.size(); i++)
    {
        if(nouns[i].location == NONE)
        {
            cout << nouns[i].word << '\n';
        }
    }
}

bool hasMysteriousKey(vector<Noun>& nouns)
{
    for (int i = 0; i < nouns.size(); i++) {
        if (nouns[i].code == MYSTERIOUS_KEY && nouns[i].location == NONE) {
            return true;
        }
    }
    return false;
}

void get (int loc, int noun, vector<Noun>& nouns)
{
    if (noun < 0)
    {
        cout << "You don't see anything like that here.\n";
        return;
    }
    if(nouns[noun].location == loc)
    {
        nouns[noun].location = NONE;
        cout << "You now have the " << nouns[noun].word << '\n';
    }
    else
    {
        cout << "You must have imagined it, because there is nothing like that here.\n";
    }
}

void drop (int loc, int noun, vector<Noun>& nouns)
{
    if (noun < 0)
    {
        cout << "You don't have anything like that.\n";
        return;
    }
    if(nouns[noun].location == NONE)
    {
        nouns[noun].location = loc;
        cout << "You leave the " << nouns[noun].word << " behind.\n";
    }
    else
    {
        cout << "You do not have anything like that on you.\n";
    }
}

void use (int loc, int noun, vector<Noun>& nouns)
{
    cout << "You use the item...\n";
    if (noun <0)
    {
        cout << "You don't have anything like that.\n";
        return;
    }
    if(noun == OLD_COIN)
    {
        cout << "You flip the coin and catch it.\nIt's heads.\nOn the heads side there seems to be the founder's face.\n";
    }
    else if(noun == EMPTY_ALE_BOTTLE)
    {
        cout << "You look inside the bottle for a last drop.\nThere is nothing left, but it does have a floral smell.\nThis bottle seems to be reuseable.\n";
    }
    else if(noun == BASKET_OF_EGGS)
    {
        cout << "You count the eggs, there are a bakers dozen.\n";
    }
    else if(noun == DOG_BONE)
    {
        cout << "You toss the bone up in the air and catch it.\n";
    }
    else if(noun == NEWS_PAPER)
    {
        cout << "You read the section that talks about local sales happening in the shopping center.\n";
    }
    else if(noun == LOST_RING)
    {
        cout << "You try on the ring.\nIt's too small to fit your fingers.\n";
    }
    else if(noun == WATERING_CAN)
    {
        cout << "You fill up the watering can, and water a dying plant.\n";
    }
    else if(noun == COIN_PURSE)
    {
        cout << "You feel the material.\nIt is velvety. It seems like something that would belong to an elderly person.\n";
    }
    else if(noun == LOVE_POTION)
    {
        cout << "You are tempted to drink it, but then you realize that that would not be a good idea.\n";
    }
    else if(noun == FLYER)
    {
        cout << "You read that there is a reward of 100 gold.\n";
    }
    else if(noun == CHEESE_WHEEL)
    {
        cout << "You roll the cheese wheel.\nIt still rolls just fine despite the missing piece.\n";
    }
    else if(noun == RUBY)
    {
        cout << "You look at the ruby in the sunlight.\nIt sparkles.\n";
    }
    else if(noun == DAGGER)
    {
        cout << "You cut a piece of bread with it.\nYep it is sharp! When cutting the bread runes on the blade started to glow.\n";
    }
    else if(noun == COCONUT_PIECES)
    {
        cout << "You smell the coconut pieces.\nThey smell nice.\n";
    }
    else if (noun == GLOWING_STONE)
    {
        cout << "You hold the stone in your hand.\nYou see it sparkle.\n";
    }
    else if (noun == TINY_CROWN)
    {
        cout << "You put the crown on your finger and look at the almost microscopic jewels.\n";
    }
    else if (noun == MYSTERIOUS_KEY)
    {
        cout << "You look at the key closer and see that it has a old symbol on it.\n";
    }
    else if (noun == MAGICAL_RELIC)
    {
        cout << "You hold the relic in your hand.\nIt's energy is so powerful you can feel it.\n";
    }
    else if (noun == LUNCH_BOX)
    {
        cout << "You open the lunch box and see some stew in a thermos, a sandwich, and a small apple.\n";
    }
    else
    {
        cout << "You can't use that.\n";
    }
}

void examine (int loc, int noun, vector<Noun>& nouns)
{
    cout << "You stop to examine the item...\n";
    if (noun < 0)
    {
        cout << "You don't see anything like that here.\n";
        return;
    }
    if(nouns[noun].location == loc)
    {
        if(noun == OLD_COIN)
        {
            cout << "This coin looks very old, it might be worth while to put it somewhere it can be displayed.\nMaybe Town Hall would know?\n";
        }
        else if(noun == EMPTY_ALE_BOTTLE)
        {
            cout << "Bottles can be reused if cleaned properly.\nIs there a place that would reuse ale bottles?\n";
        }
        else if(noun == BASKET_OF_EGGS)
        {
            cout << "There are a mix of brown, and white eggs.\nThe basket has the smell of yeast, was it used to cover bread while it rises?\n";
        }
        else if(noun == DOG_BONE)
        {
            cout << "The bone looks like it was once part of a femur.\nYou don't really see any dogs around the villagers homes but you did notice one in the garden next to the village homes.\n";
        }
        else if(noun == NEWS_PAPER)
        {
            cout << "The headline reads 'Mayor's approval rating at an all time high despite the scandal'.\nThe mayor might need to know about this headline if he doesn't know already.\n";
        }
        else if(noun == LOST_RING)
        {
            cout << "The ring looks like a wedding ring. It's gold with a small diamond.\nMaybe someone who sells jewelery at the shopping center would know who it belongs to?\n";
        }
        else if(noun == WATERING_CAN)
        {
            cout << "The watering can is rusted, and leaves an ashy residue as you touch it.\nIt might belong to a blacksmith?\n";
        }
        else if(noun == COIN_PURSE)
        {
            cout << "The coin purse is emerald green with floral embroidery and empty.\nMaybe it was dropped after a shopping trip?\n";
        }
        else if(noun == LOVE_POTION)
        {
            cout << "The vial has a pink glow, and smells like vanilla.\nYou see a label on it that says 'The Black Cat Apothecary'.\n";
        }
        else if(noun == FLYER)
        {
            cout << "The flyer is from the adventurers guild. It shows a quest to kill goblins in the forest nearby.\n";
        }
        else if(noun == CHEESE_WHEEL)
        {
            cout << "The cheese wheel has a slice missing, but it still looks edible and fresh.\nMaybe someone would like to have it as a meal? Maybe you can take it to the houses?\n";
        }
        else if(noun == RUBY)
        {
            cout << "The ruby is small and might have been part of some sort of jewelery.\nYou have heard that the forge has jewelery made there, maybe that would be a good place to take it?\n";
        }
        else if(noun == DAGGER)
        {
            cout << "The dagger looks ornate and it has strong magical properties.\nIt might be worth looking at the more magical places in town?\n";
        }
        else if (noun == COCONUT_PIECES)
        {
            cout << "The coconut pieces are in large pieces, and smell wonderful.\nYou have heard that the horses like coconut.\n";
        }
        else if (noun == GLOWING_STONE)
        {
            cout << "The stone is clear like glass, but has a warm glow to it.\nIs there something else with a glow to it around here?\n";
        }
        else if (noun == TINY_CROWN)
        {
            cout << "The crown is small and looks like it was made for a doll.\nIt might be worth looking at the magical places in town.\n";
        }
        else if (noun == MYSTERIOUS_KEY)
        {
            cout << "The key is old and has a symbol on it.\nIt might be worth looking at the older or magical places in town.\n";
        }
        else if (noun == MAGICAL_RELIC)
        {
            cout << "The relic is small and looks like it was part of a larger piece.\nIt might be worth looking at the magical places in town.\n";
        }
        else if (noun == LUNCH_BOX)
        {
            cout << "The lunch box seems to be used a lot.\nIt has a bit of dust on it, but it's still warm. Maybe someone would like to have it back?\n";
        }
    }
    else
    {
        cout << "There isn't anything like that here.\n";
    }
}

void Journal (int villagersHelped)
{
    villagerFavorPoints = villagersHelped;
    cout << "You have helped " << villagersHelped << " villagers.\n";
    if (villagerFavorPoints == 18)
    {
        cout << "The village has noticed your acts of good will.\nThey decide to help your family.\nYour mother is healed and you are given the treasure to keep.\n";
        cout << "You have won the game!\n";
        winGame = true;
    }
}

void exchange (int loc, int noun, vector<Noun>& nouns)
{
    if (noun < 0)
    {
        cout << "You don't have anything like that.\n";
        return;
    }
    if (nouns[noun].location == NONE)
    {
        if (loc == TAVERN && noun == EMPTY_ALE_BOTTLE)
        {
            cout << "The barkeeper is thankful to have a bottle to reuse.\n";
            nouns[EMPTY_ALE_BOTTLE].location = NONE;
            nouns[EMPTY_ALE_BOTTLE].location = TAVERN;
            nouns[EMPTY_ALE_BOTTLE].canBeFound = false;
            villagerFavorPoints++;
            Journal(villagerFavorPoints);
            
        }
        else if (loc == ADVENTURERS_GUILD && noun == FLYER)
        {
            cout << "The guildmaster is curious about how a flyer ended up outside when the quest wasn't assigned, but is thankful to have it be returned.\n";
            nouns[FLYER].location = NONE;
            nouns[FLYER].location = ADVENTURERS_GUILD;
            nouns[FLYER].canBeFound = false;
            villagerFavorPoints++;
            Journal(villagerFavorPoints);
        }
        else if (loc == TOWN_HALL && noun == OLD_COIN)
        {
            cout << "You discover that this coin is a valuable piece of history.\nIt will be displayed at the town hall.\n";
            nouns[OLD_COIN].location = NONE;
            nouns[OLD_COIN].location = TOWN_HALL;
            nouns[OLD_COIN].canBeFound = false;
            villagerFavorPoints++;
            Journal(villagerFavorPoints);
        }
        else if (loc == VILLAGERS_HOUSES && noun == CHEESE_WHEEL)
        {
            cout << "There is a starving child who takes the cheese wheel and gives it to his family.\nThe family is grateful.\n";
            nouns[CHEESE_WHEEL].location = NONE;
            nouns[CHEESE_WHEEL].location = VILLAGERS_HOUSES;
            nouns[CHEESE_WHEEL].canBeFound = false;
            villagerFavorPoints++;
            Journal(villagerFavorPoints);
        }
        else if (loc == SHOPPING_CENTER && noun == LOST_RING)
        {
            cout << "The shopkeeper is surprised that you have such an important ring.\nShe is suspicious of how you got it.\n";
            nouns[LOST_RING].location = NONE;
            nouns[LOST_RING].location = SHOPPING_CENTER;
            nouns[LOST_RING].canBeFound = false;
            villagerFavorPoints++;
            Journal(villagerFavorPoints);
        }
        else if (loc == SMALL_VILLAGE_GARDEN && noun == DOG_BONE)
        {
            cout << "There is a stray dog next to the garden who begs for food everyday.\nYou give the dog the bone as a treat, and give the dog many pets.\n";
            nouns[DOG_BONE].location = NONE;
            nouns[DOG_BONE].location = BAKERY;
            nouns[DOG_BONE].canBeFound = false;
            villagerFavorPoints++;
            Journal(villagerFavorPoints);
        }
        else if (loc == BAKERY && noun == BASKET_OF_EGGS)
        {
            cout << "The baker is embarrassed that he left the eggs outside.\nHe was in a hurry and must have left them behind. He thanks you profusely.\n";
            nouns[BASKET_OF_EGGS].location = NONE;
            nouns[BASKET_OF_EGGS].location = BAKERY;
            nouns[BASKET_OF_EGGS].canBeFound = false;
            villagerFavorPoints++;
            Journal(villagerFavorPoints);
        }
        else if (loc == FORGE && noun == WATERING_CAN)
        {
            cout << "The dwarf at the forge laughs, and says he must have left it behind when he was doing errands.\nHe thanks you for returning it.\n";
            nouns[WATERING_CAN].location = NONE;
            nouns[WATERING_CAN].location = FORGE;
            nouns[WATERING_CAN].canBeFound = false;
            villagerFavorPoints++;
            Journal(villagerFavorPoints);
        }
        else if (loc == SHOPPING_CENTER && noun == COIN_PURSE)
        {
            cout << "You see an elderly woman who is frantically looking for her coin purse.\nShe is so grateful to have it back.\n";
            nouns[COIN_PURSE].location = NONE;
            nouns[COIN_PURSE].location = SHOPPING_CENTER;
            nouns[COIN_PURSE].canBeFound = false;
            villagerFavorPoints++;
            Journal(villagerFavorPoints);
        }
        else if (loc == STABLES && noun == COCONUT_PIECES)
        {
            cout << "The horses take the pieces of coconut and eat them happily.\nYou think you may have made some new friends.\n";
            nouns[COCONUT_PIECES].location = NONE;
            nouns[COCONUT_PIECES].location = STABLES;
            nouns[COCONUT_PIECES].canBeFound = false;
            villagerFavorPoints++;
            Journal(villagerFavorPoints);
        }
        else if (loc == BROKEN_FOUNTAIN && noun == DAGGER)
        {
            cout << "You put the dagger on the fountain and glowing lights appear around you. Its the fae!\nThey thank you for returning the dagger.\n";
            nouns[DAGGER].location = NONE;
            nouns[DAGGER].location = BROKEN_FOUNTAIN;
            nouns[DAGGER].canBeFound = false;
            villagerFavorPoints++;
            Journal(villagerFavorPoints);
        }
        else if (loc == FORGE && noun == RUBY)
        {
            cout << "The blacksmith's wife who is a jeweler laughs and says that she remembers this ruby, and she will fix its owners necklace.\nShe thanks you.\n";
            nouns[RUBY].location = NONE;
            nouns[RUBY].location = FORGE;
            nouns[RUBY].canBeFound = false;
            villagerFavorPoints++;
            Journal(villagerFavorPoints);
        }
        else if (loc == MAYORS_HOME && noun == NEWS_PAPER)
        {
            cout << "The mayor seems upset about the headline, and he asks you if you know anything about the scandal.\nYou tell him you don't. He is relieved.\n";
            nouns[NEWS_PAPER].location = NONE;
            nouns[NEWS_PAPER].location = MAYORS_HOME;
            nouns[NEWS_PAPER].canBeFound = false;
            villagerFavorPoints++;
            Journal(villagerFavorPoints);
        }
        else if (loc == APOTHECARY && noun == LOVE_POTION)
        {
            cout << "Ceilia is happy to have the valuable love potion returned, but she is pretty secretive about who had purchased it in the first place.\n";
            nouns[LOVE_POTION].location = NONE;
            nouns[LOVE_POTION].location = APOTHECARY;
            nouns[LOVE_POTION].canBeFound = false;
            villagerFavorPoints++;
            Journal(villagerFavorPoints);
        }
        else if (loc == ANCIENT_TREESTUMP && noun == TINY_CROWN)
        {
            cout << "A tiny mouse comes out of the stump and takes the crown.\nYou see a glow within the stump.\n";
            nouns[TINY_CROWN].location = NONE;
            nouns[TINY_CROWN].location = ANCIENT_TREESTUMP;
            nouns[TINY_CROWN].canBeFound = false;
            villagerFavorPoints++;
            Journal(villagerFavorPoints);
        }
        else if (loc == GLOWING_POND && noun == GLOWING_STONE)
        {
            cout << "You return the stone to the pond and glowing fish begin to swim around it.\nYou feel a sense of peace.\n";
            nouns[GLOWING_STONE].location = NONE;
            nouns[GLOWING_STONE].location = GLOWING_POND;
            nouns[GLOWING_STONE].canBeFound = false;
            villagerFavorPoints++;
            Journal(villagerFavorPoints);
        }
        else if (loc == WIZARD_TOWER && noun == MAGICAL_RELIC)
        {
            cout << "The wizard is surprised to see the relic.\nHe tells you that it is a piece of a larger relic that is very powerful. He thanks you for returning it.\n";
            nouns[MAGICAL_RELIC].location = NONE;
            nouns[MAGICAL_RELIC].location = WIZARD_TOWER;
            nouns[MAGICAL_RELIC].canBeFound = false;
            villagerFavorPoints++;
            Journal(villagerFavorPoints);
        }
        else if (loc == GRAVEYARD && noun == LUNCH_BOX)
        {
            cout << "The gravekeeper is happy to have his lunch box back.\nHe tells you that he was so hungry he forgot it. He thanks you.\n";
            nouns[LUNCH_BOX].location = NONE;
            nouns[LUNCH_BOX].location = GRAVEYARD;
            nouns[LUNCH_BOX].canBeFound = false;
            villagerFavorPoints++;
            Journal(villagerFavorPoints);
        }
            nouns[noun].location = loc;
    }
    else
    {
        cout << "You can't exchange that here.\n";
    }
}

void talkToVillagers(int loc, vector<Room>& rooms)
{
    if (loc == SOUTH_MAIN_ROAD)
    {
        cout << "You talk to a small child playing with their friends.\nThey say that they saw a fae the other day.\n";
    }
    if (loc == NORTH_MAIN_ROAD)
    {
        cout << "You talk to a young woman who seems a bit vain. She tells you that her relationship with the mayor is no ones business.\n";
    }
    if (loc == SHOPPING_CENTER)
    {
        cout << "You talk to a vendor who tells you that she saw a woman fighting with her husband yesterday.\n";
    }
    if (loc == FORGE)
    {
        cout << "You talk to the dwarf and he seems irritated. He says that he is missing an important tool.\nHis wife is a jeweler, and asks him where was the last place he saw it.\n";
    }
    if (loc == APOTHECARY)
    {
        cout << "Ceilia seems worried. She tells you that someone important came to buy an illegal potion, and she's afraid to be charged with a crime\n";
    }
    if (loc == TAVERN)
    {
        cout << "The barkeeper tells you that he's noticed the fae more around town.\nRumors are that the mayor seems like he's hiding something.\n";
    }
    if (loc == ADVENTURERS_GUILD)
    {
        cout << "The guildmaster tells you that the mayor has been acting strange lately.\nHe's been seen talking to himself and looking at the fae.\nHe's also been talking to the wizard's daughter.\n";
    }
    if (loc == ANCIENT_TREESTUMP)
    {
        cout << "No one seems to be here, but you hear a voice in your head.\nIt says 'The fae are in danger, you must help them'.\n";
    }
    if (loc == GLOWING_POND)
    {
        cout << "You talk to an old woman who tells you that she leaves food out for the fae.\nShe says that they are the protectors of the village.\n";
    }
    if (loc == VILLAGERS_HOUSES)
    {
        cout << "You see a mom and her kids playing.\nShe tells you that she's noticed a stray dog in the garden.\nShe's worried that it might be hungry.\n";
    }
    if (loc == SMALL_VILLAGE_GARDEN)
    {
        cout << "You talk to the old dog. He whines and looks at you with sad soulful eyes.\n";
    }
    if (loc == STABLES)
    {
        cout << "There is a stablehand who tells you that the horses have been acting strange lately.\nThey seem to be spooked by something.\n";
    }
    if (loc == PASTURE)
    {
        cout << "A young woman is feeding the horses.\nShe tells you that she's trying to feed her horse Daisy, but she only wants coconut.\nShe sighs and says she will just go back to the stables\n";
    }
    if (loc == BRIDGE)
    {
        cout << "You talk to a fisherman who tells you that he has seen a glowing fish in the river.\nHe says that it's a good omen.\n";
    }
    if (loc == PATH_OUT_OF_TOWN)
    {
        cout << "You see young adventurers who are talking about the quest to kill the troll.\nThey seem excited and nervous.\n";
    }
    if (loc == FORGOTTEN_PATH)
    {
        cout << "There is no one around, but there is an uneasy feeling in the air.\n";
    }
    if (loc == ABANDONED_HOUSE)
    {
        cout << "A ghostly figure appears and tells you that the mayor has been looking for this house.\nHe says that the mayor is hiding something.\n";
    }
    if (loc == OVERGROWN_GARDEN)
    {
        cout << "You look around for someone to talk to, but no one is here...\n";
    }
    if (loc == BROKEN_FOUNTAIN)
    {
        cout << "You think you hear voices, but as soon as you move, they go away.\n";
    }
    if (loc == GRAVEYARD)
    {
        cout << "You talk to the gravekeeper who tells you that he's seen the mayor talking to the fae.\nHe says that the mayor is hiding something.\n";
    }
    if (loc == SIDE_ROAD)
    {
        cout << "You see an old woman talking to her grandson.\nShe asks him to get some bread from the bakery.\n";
    }
    if (loc == BAKERY)
    {
        cout << "You see the head baker.\nHe seems worried that he cannot find all of his ingredients.\n";
    }
    if (loc == TOWN_HALL)
    {
        cout << "You see the council members talking about the mayor.\nThey seem to be arguing about something.\n";
    }
    if (loc == FOUNDERS_STATUE)
    {
        cout << "You see the mayor's wife talking to the statue.\nShe seems to be crying.\n";
    }
    if (loc == MAYORS_HOME)
    {
        cout << "You see the mayor pacing around his home.\nHe seems to be talking to himself.\n";
    }
    if (loc == WIZARD_TOWER)
    {
        cout << "The wizard looks at you and seems annoyed.\nHe tells you that he's been busy and doesn't have time for you.\n";
    }
}

void Observe (int loc, vector<Room>& rooms)
{
    if (loc == SOUTH_MAIN_ROAD)
    {
        cout << "You see children running and playing with wooden swords.\nThey seem to be pretending to be adventurers.\n";
    }
    if (loc == NORTH_MAIN_ROAD)
    {
        cout << "You see villagers walking to and from the shopping center.\nThey seem to be in a hurry.\n";
    }
    if (loc == SHOPPING_CENTER)
    {
        cout << "You see many vendors selling their wares.\nThere is a lot of noise and people talking.\nThere is an old woman looking for something.\n";
    }
    if (loc == SIDE_ROAD)
    {
        cout << "This road seems a lot quiter than the main roads.\nYou see council members walking to the town hall.\n";
    }
    if (loc == GLOWING_POND)
    {
        cout << "The pond has a soft blue glow to it.\nYou see fish swimming around.\n";
    }
    if (loc == BRIDGE)
    {
        cout << "The river below is flowing quickly.\nYou see a fisherman trying to catch fish.\n";
    }
    if (loc == PATH_OUT_OF_TOWN)
    {
        cout << "You see young adventurers talking about the quest to kill the troll.\nThey seem excited and nervous.\n";
    }
    if (loc == FORGOTTEN_PATH)
    {
        cout << "The path is overgrown with weeds and thorns.\nThere is a haze in the air.\n";
    }
    if (loc == ABANDONED_HOUSE)
    {
        cout << "The house is falling apart.\nYou see a ghostly figure in the window.\n";
    }
    if (loc == OVERGROWN_GARDEN)
    {
        cout << "The garden is overgrown with beautiful flowers.\nThis was once a prized garden.\n";
    }
    if (loc == BROKEN_FOUNTAIN)
    {
        cout << "The fountain is broken and the water is stagnant.\nYou see an alter on the edge of the fountain.\n";
    }
    if (loc == GRAVEYARD)
    {
        cout << "The graveyard is quiet.\nYou see the gravekeeper tending to the graves.\n";
    }
    if (loc == VILLAGERS_HOUSES)
    {
        cout << "The houses are quaint and well kept.\nYou see children playing in the yards.\nYou notice a family that doesn't seem to have enough food.\n";
    }
    if (loc == SMALL_VILLAGE_GARDEN)
    {
        cout << "The garden is well kept.\nYou see a dog sleeping in the sun.\n";
    }
    if (loc == STABLES)
    {
        cout << "The stables are clean and well kept.\nYou see the stablehand feeding the horses.\n";
    }
    if (loc == PASTURE)
    {
        cout << "The pasture is peaceful.\nYou see many horses grazing\n";
    }
    if (loc == WINE_CELLAR)
    {
        cout << "The cellar is dark and damp.\nYou see many cobwebs and dust.\nThere is lots of wine bottles on the shelves.\nThere is an old chest in the corner.\n";
    }
    if (loc == ANCIENT_TREESTUMP)
    {
        cout << "The tree stump is ancient and covered in moss.\nYou see a small hole in the side of the stump.\n";
    }
    if (loc == APOTHECARY)
    {
        cout << "The apothecary is filled with herbs and potions.\nYou see Ceilia behind the counter.\n";
    }
    if (loc == TAVERN)
    {
        cout << "The tavern is filled with people talking and laughing.\nYou see the barkeeper behind the bar.\n";
    }
    if (loc == ADVENTURERS_GUILD)
    {
        cout << "The guild is filled with adventurers talking about their quests.\nYou see the guildmaster behind the counter\n";
    }
    if (loc == FORGE)
    {
        cout << "The forge is hot and noisy.\nYou see the dwarf working on a sword.\nHis wife is a jeweler and is working on a necklace.\n";
    }
    if (loc == BAKERY)
    {
        cout << "The bakery is filled with the smell of fresh bread.\nAll of the breads available look heavenly!\nYou see the head baker behind the counter.\n";
    }
    if (loc == TOWN_HALL)
    {
        cout << "The town hall is filled with council members talking.\nYou see a small museum in the corner.\n";
    }
    if (loc == MAYORS_HOME)
    {
        cout << "The mayor's home is quiet.\nYou see the mayor pacing in his study.\n";
    }
    if (loc == FOUNDERS_STATUE)
    {
        cout << "The statue is of the founder of the village.\nIt is well kept and has a plaque with the history of the village.\n";
    }
    if (loc == WIZARD_TOWER)
    {
        cout << "There is all sorts of magical items in the tower.\nYou see the wizard working on a potion.\n";
    }
}

void Listen (int loc, vector<Room>& rooms)
{
    if (loc == SOUTH_MAIN_ROAD)
    {
        cout << "You hear children laughing and playing.\n";
    }
    if (loc == NORTH_MAIN_ROAD)
    {
        cout << "You hear people talking as they walk to the shopping center.\n";
    }
    if (loc == SIDE_ROAD)
    {
        cout << "You hear birds chirping and the footsteps of the council members.\n";
    }
    if (loc == GLOWING_POND)
    {
        cout << "You hear leaves rustling and the sound of water.\n";
    }
    if (loc == BRIDGE)
    {
        cout << "You hear the river flowing and the fisherman talking to himself.\n";
    }
    if (loc == PATH_OUT_OF_TOWN)
    {
        cout << "You hear the adventurers talking about the quest to kill the troll.\n";
    }
    if (loc == FORGOTTEN_PATH)
    {
        cout << "You hear the wind blowing through the trees.\n";
    }
    if (loc == ABANDONED_HOUSE)
    {
        cout << "You hear the creaking of the house and the ghostly figure talking to itself.\n";
    }
    if (loc == OVERGROWN_GARDEN)
    {
        cout << "You hear the buzzing of bees and the rustling of leaves.\n";
    }
    if (loc == BROKEN_FOUNTAIN)
    {
        cout << "You hear the water dripping and the sound of the alter.\nYou hear tiny whispers in the air.\n";
    }
    if (loc == GRAVEYARD)
    {
        cout << "You hear the gravekeeper singing to himself and the wind blowing through the trees.\n";
    }
    if (loc == VILLAGERS_HOUSES)
    {
        cout << "You hear children playing and the sound of a mother calling her children.\n";
    }
    if (loc == SMALL_VILLAGE_GARDEN)
    {
        cout << "You hear the dog snoring and the sound of the wind.\n";
    }
    if (loc == STABLES)
    {
        cout << "You hear the horses neighing and the stablehand talking to the horses.\n";
    }
    if (loc == PASTURE)
    {
        cout << "You hear the horses grazing and the sound of the wind.\n";
    }
    if (loc == WINE_CELLAR)
    {
        cout << "You hear dripping water from what you assume is a leaky ceiling.\nThe water droplets echo in the dark.\n";
    }
    if (loc == ANCIENT_TREESTUMP)
    {
        cout << "You hear the wind blowing through the trees and tiny giggles.\n";
    }
    if (loc == APOTHECARY)
    {
        cout << "You hear the sound of Ceilia mixing potions and the sound of the door opening and closing.\n";
    }
    if (loc == TAVERN)
    {
        cout << "You hear the sound of people talking and laughing.\nYou hear the barkeeper talking to the patrons.\n";
    }
    if (loc == ADVENTURERS_GUILD)
    {
        cout << "You hear the sound of the guildmaster talking to the adventurers.\nYou hear the sound of the door opening and closing.\n";
    }
    if (loc == FORGE)
    {
        cout << "You hear the sound of the dwarf hammering on the sword.\nYou hear the sound of the jeweler working on the necklace.\n";
    }
    if (loc == BAKERY)
    {
        cout << "You hear the sound of the head baker talking to the customers.\nYou hear the ovens and the metal pans\n";
    }
    if (loc == TOWN_HALL)
    {
        cout << "You hear the sound of the council members talking in hushed tones.\nThey talk about the mayor and the wizard's daughter.\n";
    }
    if (loc == MAYORS_HOME)
    {
        cout << "You hear the mayor talking to himself and what you assume is the mayors wife crying.\n";
    }
    if (loc == FOUNDERS_STATUE)
    {
        cout << "You hear birds chirping and the sound of the wind.\n";
    }
    if (loc == SHOPPING_CENTER)
    {
        cout << "You hear the sound of the vendors selling their wares.\nYou hear the sound of an old woman asking about her coin purse.\n";
    }
    if (loc == WIZARD_TOWER)
    {
        cout << "You hear the sound of the wizard mixing potions and the sound of the wizard talking to himself in an angry tone.\n";
    }
}

void search (int loc, vector<Noun>& nouns, vector<Room>& rooms)
{
    cout << "You look around carefully...\n";
    for(int i = 0; i < NOUNS; i++)
    {
        if(nouns[i].location == loc && nouns[i].canBeFound == true)
        {
            cout << "You found a " << nouns[i].word << " " << nouns[i].description << '\n';
        }
    }
}

bool parser(int &loc, string& wd1, string& wd2, vector<Word>& dir, vector<Word>& vbs, vector<Room>& rooms, vector<Noun>& nouns)
{
    static bool doorIsOpen = false;
    int i;
    for(i = 0; i < DIRS; i++)
    {
        if(wd1 == dir[i].str)
        {
            if(rooms[loc].exits[dir[i].code] != NONE && rooms[loc].exits[dir[i].code] < ROOMS)
            {
                loc = rooms[loc].exits[dir[i].code];
                cout << "I am now at " << rooms[loc].description << ".\n";
                return true;
            }
            else
            {
                cout << "No exit that way.\n";
                return true;
            }
        }
    }

    int VERB_ACTION = NONE;
    int NOUN_MATCH = NONE;

    for (i = 0; i < VERBS; i++)
    {
        if(wd1 == vbs[i].str)
        {
            VERB_ACTION = vbs[i].code;
            break;
        }
    }

    if(wd2 != "")
    {
        for(i = 0; i < NOUNS; i++)
        {
            if(wd2 == nouns[i].word)
            {
                NOUN_MATCH = nouns[i].code;
                break;
            }
        }
    }
    if(VERB_ACTION == NONE)
    {
        cout << "No valid command entered.\n";
        return true;
    }
    if(VERB_ACTION == LOOK)
    {
        look_around(loc, rooms, dir);
        return true;
    }
    if(VERB_ACTION == OPEN)
    {
        if(NOUN_MATCH == CELLAR_DOOR && loc == GLOWING_POND || loc == WINE_CELLAR)
        {
            if(loc == GLOWING_POND || loc == WINE_CELLAR)
            {
                if(doorIsOpen == false)
                {
                    doorIsOpen = true;
                    rooms[GLOWING_POND].exits[EAST] = WINE_CELLAR;
                    rooms[WINE_CELLAR].exits[WEST] = GLOWING_POND;
                    nouns[CELLAR_DOOR].description.clear();
                    nouns[CELLAR_DOOR] = Noun("Cellar Door", "a hidden wine cellar door", CELLAR_DOOR, WINE_CELLAR, false);
                    cout << "The door is now open. You can see a lot of old untouched wine bottles.\nThere's a layer of dust on each bottle.\nThere is a small chest in the corner.\nCan you open it?\n";
                    return true;
                }
                else if (doorIsOpen == true)
                {
                    cout << "The door is already open.\n";
                    return true;
                }
            }
            else
            {
                cout << "There is no door to open here\n";
                return true;
            }
        }
        else
        {
            cout << "Opening that is not possible.\n";
            return true;   
        }
    }
    if (VERB_ACTION == CLOSE)
    {
        if(NOUN_MATCH == CELLAR_DOOR && loc == GLOWING_POND || loc == WINE_CELLAR)
        {
            if(loc == GLOWING_POND || loc == WINE_CELLAR)
            {
                if(doorIsOpen == true)
                {
                    doorIsOpen = false;
                    rooms[GLOWING_POND].exits[EAST] = NONE;
                    rooms[WINE_CELLAR].exits[WEST] = GLOWING_POND;
                    nouns[CELLAR_DOOR].description.clear();
                    nouns[CELLAR_DOOR] = Noun("Cellar Door", "a mysterious moss covered door", CELLAR_DOOR, WINE_CELLAR, false);
                    cout << "The door is now closed.\n";
                    return true;
                }
                else if (doorIsOpen == false)
                {
                    cout << "The door is already closed.\n";
                    return true;
                }
            }
            else
            {
                cout << "There is no door to close here.\n";
                return true;
            }
        }
        else
        {
            cout << "Closing that is not possible.\n";
            return true;
        }
    }
    if (VERB_ACTION == CHEST)
    {
        if (loc == WINE_CELLAR && hasMysteriousKey(nouns))
        {
            cout << "You open the chest and there is treasure! Your search is over!\n";
            winGame = true;
            return true;
        }
        else
        {
            cout << "You try your hardest to open the chest, but it won't budge...\n";
            return true;
        }
    }
    if(VERB_ACTION == INVENTORY)
    {
        inventory(nouns);
    }
    if(VERB_ACTION == GET)
    {
        if(NOUN_MATCH != NONE)
        {
            get(loc, NOUN_MATCH, nouns);
        }
        else if(NOUN_MATCH == NONE)
        {
            cout << "You don't see anything like that here.\n";
        }
    }
    if(VERB_ACTION == DROP)
    {
        if(NOUN_MATCH != NONE)
        {
            drop(loc, NOUN_MATCH, nouns);
        }
        else if(NOUN_MATCH == NONE)
        {
            cout << "You don't have anything like that.\n";
        }
    }
    if(VERB_ACTION == USE)
    {
        if(NOUN_MATCH != NONE)
        {
            use(loc, NOUN_MATCH, nouns);
        }
        else if(NOUN_MATCH == NONE)
        {
            cout << "You don't have anything like that.\n";
        }
    }
    if(VERB_ACTION == EXAMINE)
    {
        if(NOUN_MATCH != NONE)
        {
            examine(loc, NOUN_MATCH, nouns);
        }
        else if(NOUN_MATCH == NONE)
        {
            cout << "You don't see anything like that here.\n";
        }
    }
    if(VERB_ACTION == SEARCH)
    {
        search(loc, nouns, rooms);
    }
    if(VERB_ACTION == EXCHANGE)
    {
        exchange(loc, NOUN_MATCH, nouns);
    }
    if (VERB_ACTION == TALK)
    {
        talkToVillagers(loc, rooms);
    }
    if (VERB_ACTION == OBSERVE)
    {
        Observe(loc, rooms);
    }
    if (VERB_ACTION == LISTEN)
    {
        Listen(loc, rooms);
    }
    if (VERB_ACTION == JOURNAL)
    {
        Journal(villagerFavorPoints);
    }
    
    return false;
    }

int main()
{
    
    string command;
    string word_1;
    string word_2;

    vector<Room> rooms;
    vector<Word> directions;
    vector<Word> verbs;
    vector<Noun> nouns;

    int location = SOUTH_MAIN_ROAD;
    
    set_rooms(rooms);
    set_directions(directions);
    set_verbs(verbs);
    set_nouns(nouns);
    randomItemLocations(nouns);

    cout << "to search the room for an item type 'search'.\n";
    cout << "to look around the room for exits type 'look'.\n";
    cout << "to get an item in a room type 'get' and the item name.\n";
    cout << "to drop an item from your inventory type 'drop' and the item name.\n";
    cout << "to use an item from inventory type 'use' and the item name.\n";
    cout << "to examine an item in a room type 'examine' and the item name.\n";
    cout << "to open a door type 'open'.\n";
    cout << "to close a door type 'close'.\n";
    cout << "to exchange an item in your inventory type 'exchange' and the item name.\n";
    cout << "to see your inventory type 'inventory'.\n";
    cout << "to move type the direction you want to go.\n";
    cout << "to talk to villagers type 'talk'.\n";
    cout << "to observe the area type 'observe'.\n";
    cout << "to listen to the area type 'listen'.\n";
    cout << "to see how many villagers you have helped type 'journal'.\n";
    cout << "To open the chest type 'chest'.\n";
    cout << "to quit type 'quit'.\n";
    cout << "You are a young villager who has a sick mother\nYou have heard from the wizard north of town that a pirate hid treasure in the village long ago\nYou want to find this treasure to save your mother.\n";
    while(word_1 != "QUIT" && winGame == false)
    {
        command.clear();
        cout << "What shall I do? ";
        getline(cin, command);

        word_1.clear();
        word_2.clear();

        section_command(command, word_1, word_2);
        if(word_1 != "QUIT")
        {
            parser(location, word_1, word_2, directions, verbs, rooms, nouns);
        }
    }
    return 0;
}
    
    
