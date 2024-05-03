#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;

enum en_DIRS {NORTH, EAST, SOUTH, WEST};
enum en_ROOMS {SOUTH_MAIN_ROAD, TAVERN, ANCIENT_TREESTUMP, ADVENTURERS_GUILD, FORGE, GLOWING_POND, WINE_CELLAR, STABLES, PATH_OUT_OF_TOWN, BRIDGE, PASTURE, SIDE_ROAD, TOWN_HALL, FOUNDERS_STATUE, NORTH_MAIN_ROAD, BAKERY, FORGOTTEN_PATH, GRAVEYARD, ABANDONED_HOUSE, OVERGROWN_GARDEN, VILLAGERS_HOUSES, SMALL_VILLAGE_GARDEN, MAYORS_HOME, BROKEN_FOUNTAIN, SHOPPING_CENTER, APOTHECARY};
enum en_VERBS {GET, DROP, USE, OPEN, CLOSE, EXAMINE, INVENTORY, LOOK, SEARCH,EXCHANGE};
enum en_NOUNS {CELLAR_DOOR, OLD_COIN, EMPTY_ALE_BOTTLE, BASKET_OF_EGGS, DOG_BONE, NEWS_PAPER, LOST_RING, WATERING_CAN, COIN_PURSE, LOVE_POTION, FLYER, CHEESE_WHEEL, RUBY, DAGGER, COCONUT_PIECES};

const int NONE = -1;
const int DIRS = 4;
const int ROOMS = 26;
const int VERBS = 10;
const int NOUNS = 15;

class Room {
public:
    string description;
    int exits[DIRS];

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

    rooms[TAVERN] = Room("The Tavern. Loud tavern with a bar, and rooms for rent. There seems to be lost of empty bottles behind the bar in a basket.");
    rooms[TAVERN].exits[NORTH] = SHOPPING_CENTER;
    rooms[TAVERN].exits[EAST] = NONE;
    rooms[TAVERN].exits[SOUTH] = NONE;
    rooms[TAVERN].exits[WEST] = SOUTH_MAIN_ROAD;

    rooms[ANCIENT_TREESTUMP] = Room("The forgotten ancient treestump. This old stump once was the home of the fae. There appear to be small footprints around it.");
    rooms[ANCIENT_TREESTUMP].exits[NORTH] = NONE;
    rooms[ANCIENT_TREESTUMP].exits[EAST] = NORTH_MAIN_ROAD;
    rooms[ANCIENT_TREESTUMP].exits[SOUTH] = ADVENTURERS_GUILD;
    rooms[ANCIENT_TREESTUMP].exits[WEST] = NONE;

    rooms[ADVENTURERS_GUILD] = Room("The local adventurers guild. A place for adventurers to gather, drink, and rest. There is a large orc at the front desk and behind him is a bulletin board.");
    rooms[ADVENTURERS_GUILD].exits[NORTH] = ANCIENT_TREESTUMP;
    rooms[ADVENTURERS_GUILD].exits[EAST] = SOUTH_MAIN_ROAD;
    rooms[ADVENTURERS_GUILD].exits[SOUTH] = NONE;
    rooms[ADVENTURERS_GUILD].exits[WEST] = NONE;

    rooms[FORGE] = Room("Dwarven forge with a few beautifully crafted swords on display. The blacksmith seems to be upset about losing a tool, and his wife is making jewelery.");
    rooms[FORGE].exits[NORTH] = NONE;
    rooms[FORGE].exits[EAST] = NONE;
    rooms[FORGE].exits[SOUTH] = NONE;
    rooms[FORGE].exits[WEST] = SHOPPING_CENTER;

    rooms[GLOWING_POND] = Room("The beautiful glowing pond. The pond here emits a mysterious glow. It's in the center of new village. There is a huge willow tree next to it.");
    rooms[GLOWING_POND].exits[NORTH] = BRIDGE;
    rooms[GLOWING_POND].exits[EAST] = WINE_CELLAR;
    rooms[GLOWING_POND].exits[SOUTH] = NORTH_MAIN_ROAD;
    rooms[GLOWING_POND].exits[WEST] = VILLAGERS_HOUSES;

    rooms[WINE_CELLAR] = Room("hidden wine cellar by the pond. It is partially covered by bushes. Is it still in use?");
    rooms[WINE_CELLAR].exits[NORTH] = NONE;
    rooms[WINE_CELLAR].exits[EAST] = NONE;
    rooms[WINE_CELLAR].exits[SOUTH] = NONE;
    rooms[WINE_CELLAR].exits[WEST] = NONE;

    rooms[STABLES] = Room("The stables. Many horses are kept here. The smell of hay and manure is strong. The horses seem to be enjoying some fruit.");
    rooms[STABLES].exits[NORTH] = PASTURE;
    rooms[STABLES].exits[EAST] = VILLAGERS_HOUSES;
    rooms[STABLES].exits[SOUTH] = NONE;
    rooms[STABLES].exits[WEST] = NONE;

    rooms[PATH_OUT_OF_TOWN] = Room("The path out of town. A path leading out of town. It looks a bit rough. There is a directional sign that has directions everywhere but to the east which has been scratched out.");
    rooms[PATH_OUT_OF_TOWN].exits[NORTH] = NONE;
    rooms[PATH_OUT_OF_TOWN].exits[EAST] = FORGOTTEN_PATH;
    rooms[PATH_OUT_OF_TOWN].exits[SOUTH] = BRIDGE;
    rooms[PATH_OUT_OF_TOWN].exits[WEST] = NONE;

    rooms[BRIDGE] = Room("The bridge going out of town. A stone bridge that leads to the path out of town. It looks newly built. The river below is full of fish.");
    rooms[BRIDGE].exits[NORTH] = PATH_OUT_OF_TOWN;
    rooms[BRIDGE].exits[EAST] = NONE;
    rooms[BRIDGE].exits[SOUTH] = GLOWING_POND;
    rooms[BRIDGE].exits[WEST] = NONE;

    rooms[PASTURE] = Room("peaceful pasture which adventurers horses come to graze. The horses seem to be at happy here. ");
    rooms[PASTURE].exits[NORTH] = NONE;
    rooms[PASTURE].exits[EAST] = NONE;
    rooms[PASTURE].exits[SOUTH] = STABLES;
    rooms[PASTURE].exits[WEST] = NONE;

    rooms[SIDE_ROAD] = Room("Small road off of the main road. A small side road that leads to the important places in town. It's a bit quieter here. The road is a bit rough.");
    rooms[SIDE_ROAD].exits[NORTH] = SOUTH_MAIN_ROAD;
    rooms[SIDE_ROAD].exits[EAST] = FOUNDERS_STATUE;
    rooms[SIDE_ROAD].exits[SOUTH] = TOWN_HALL;
    rooms[SIDE_ROAD].exits[WEST] = BAKERY;

    rooms[TOWN_HALL] = Room("great town hall. The place where the mayor and council meet. It has a guardian statue in front it looks like a dragon. inside there is a small museum.");
    rooms[TOWN_HALL].exits[NORTH] = SIDE_ROAD;
    rooms[TOWN_HALL].exits[EAST] = NONE;
    rooms[TOWN_HALL].exits[SOUTH] = NONE;
    rooms[TOWN_HALL].exits[WEST] = NONE;

    rooms[FOUNDERS_STATUE] = Room("founder's statue. A statue of the mayors great grandfather who took the village away from the fae with the help of his pet dragon.");
    rooms[FOUNDERS_STATUE].exits[NORTH] = MAYORS_HOME;
    rooms[FOUNDERS_STATUE].exits[EAST] = NONE;
    rooms[FOUNDERS_STATUE].exits[SOUTH] = NONE;
    rooms[FOUNDERS_STATUE].exits[WEST] = SIDE_ROAD;

    rooms[MAYORS_HOME] = Room("mayors home. It's a large house compared to the others in the village. The mayor seems to be distraught about something.");
    rooms[MAYORS_HOME].exits[NORTH] = NONE;
    rooms[MAYORS_HOME].exits[EAST] = NONE;
    rooms[MAYORS_HOME].exits[SOUTH] = FOUNDERS_STATUE;
    rooms[MAYORS_HOME].exits[WEST] = NONE;

    rooms[NORTH_MAIN_ROAD] = Room("northern main road of the village.");
    rooms[NORTH_MAIN_ROAD].exits[NORTH] = GLOWING_POND;
    rooms[NORTH_MAIN_ROAD].exits[EAST] = SHOPPING_CENTER;
    rooms[NORTH_MAIN_ROAD].exits[SOUTH] = SOUTH_MAIN_ROAD;
    rooms[NORTH_MAIN_ROAD].exits[WEST] = ANCIENT_TREESTUMP;

    rooms[BAKERY] = Room("popular bakery. This bakery is known throughout the kingdom for exceptional pastries.\nMany adventurers come to learn how to bake.\nThe smell of fresh bread fills the air.");
    rooms[BAKERY].exits[NORTH] = NONE;
    rooms[BAKERY].exits[EAST] = SIDE_ROAD;
    rooms[BAKERY].exits[SOUTH] = NONE;
    rooms[BAKERY].exits[WEST] = NONE;

    rooms[FORGOTTEN_PATH] = Room("forgotten path. It's easy to miss this path. It's overgrown and has an eerie feel to it. There seems to be a magical presence here.");
    rooms[FORGOTTEN_PATH].exits[NORTH] = NONE;
    rooms[FORGOTTEN_PATH].exits[EAST] = GRAVEYARD;
    rooms[FORGOTTEN_PATH].exits[SOUTH] = ABANDONED_HOUSE;
    rooms[FORGOTTEN_PATH].exits[WEST] = PATH_OUT_OF_TOWN;

    rooms[GRAVEYARD] = Room("rumored to be haunted graveyard. An old graveyard that has been long forgotten. These graves are from the time of the fae. The headstones are worn and hard to read. There is a ominous fog here.");
    rooms[GRAVEYARD].exits[NORTH] = NONE;
    rooms[GRAVEYARD].exits[EAST] = NONE;
    rooms[GRAVEYARD].exits[SOUTH] = NONE;
    rooms[GRAVEYARD].exits[WEST] = FORGOTTEN_PATH;

    rooms[ABANDONED_HOUSE] = Room("abandoned house. This house is rumored to have been inhabited by a witch that helped the fae.\nNow it's rickety and falling apart.\nYou think you might have seen a small light, but it's probably your imagination.");
    rooms[ABANDONED_HOUSE].exits[NORTH] = FORGOTTEN_PATH;
    rooms[ABANDONED_HOUSE].exits[EAST] = NONE;
    rooms[ABANDONED_HOUSE].exits[SOUTH] = OVERGROWN_GARDEN;
    rooms[ABANDONED_HOUSE].exits[WEST] = NONE;

    rooms[OVERGROWN_GARDEN] = Room("garden behind the house. You think this might have been a wonderful garden at one point. There are many flowers and herbs growing here despite it being abandoned. You hear the sound of a fountain nearby.");
    rooms[OVERGROWN_GARDEN].exits[NORTH] = ABANDONED_HOUSE;
    rooms[OVERGROWN_GARDEN].exits[EAST] = BROKEN_FOUNTAIN;
    rooms[OVERGROWN_GARDEN].exits[SOUTH] = NONE;
    rooms[OVERGROWN_GARDEN].exits[WEST] = NONE;

    rooms[VILLAGERS_HOUSES] = Room("neighborhood which the villagers live. There are many beautiful houses made of stone and wood. The building style is tudor. The villagers seem to be friendly. You see some beggars near the road.");
    rooms[VILLAGERS_HOUSES].exits[NORTH] = SMALL_VILLAGE_GARDEN;
    rooms[VILLAGERS_HOUSES].exits[EAST] = GLOWING_POND;
    rooms[VILLAGERS_HOUSES].exits[SOUTH] = NONE;
    rooms[VILLAGERS_HOUSES].exits[WEST] = STABLES;

    rooms[SMALL_VILLAGE_GARDEN] = Room("small garden to the north of the neighborhood. A small community garden where villagers grow many varieties of vegetables and herbs to share with their community. There is an old dog who waits for treats.");
    rooms[SMALL_VILLAGE_GARDEN].exits[NORTH] = NONE;
    rooms[SMALL_VILLAGE_GARDEN].exits[EAST] = NONE;
    rooms[SMALL_VILLAGE_GARDEN].exits[SOUTH] = VILLAGERS_HOUSES;
    rooms[SMALL_VILLAGE_GARDEN].exits[WEST] = NONE;

    rooms[BROKEN_FOUNTAIN] = Room("broken fountain. This fountain is broken and has been for a long time.\nIt's beautifully crafted and has a small plaque that reads 'Always remember the fae'. There are runes on the base of the fountain.");
    rooms[BROKEN_FOUNTAIN].exits[NORTH] = NONE;
    rooms[BROKEN_FOUNTAIN].exits[EAST] = NONE;
    rooms[BROKEN_FOUNTAIN].exits[SOUTH] = NONE;
    rooms[BROKEN_FOUNTAIN].exits[WEST] = OVERGROWN_GARDEN;

    rooms[SHOPPING_CENTER] = Room("busy shopping center. A large area where there are many shop stalls with the sounds of people haggling and the smells of many foods. There are stalls for many things here. Many villagers are here shopping.");
    rooms[SHOPPING_CENTER].exits[NORTH] = APOTHECARY;
    rooms[SHOPPING_CENTER].exits[EAST] = FORGE;
    rooms[SHOPPING_CENTER].exits[SOUTH] = TAVERN;
    rooms[SHOPPING_CENTER].exits[WEST] = NORTH_MAIN_ROAD;

    rooms[APOTHECARY] = Room("Black Cat Apothecary. A small shop with potions and herbs that are said to have magical properties.\nThe shopkeeper is a very mysterious elf.");
    rooms[APOTHECARY].exits[NORTH] = NONE;
    rooms[APOTHECARY].exits[EAST] = NONE;
    rooms[APOTHECARY].exits[SOUTH] = SHOPPING_CENTER;
    rooms[APOTHECARY].exits[WEST] = NONE;
    
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
}

void set_nouns(vector<Noun>& nouns)
{
    nouns.resize(NOUNS);
    nouns[CELLAR_DOOR] = Noun("Cellar DOOR", "A mysterious moss covered door.", CELLAR_DOOR, WINE_CELLAR, false);
    nouns[OLD_COIN] = Noun("OLD COIN", "an old coin looks like it's from the fae era.", OLD_COIN, NONE, true);
    nouns[EMPTY_ALE_BOTTLE] = Noun("EMPTY ALE BOTTLE", "Looks like it was left here recently. Littering is bad.", EMPTY_ALE_BOTTLE, NONE, true);
    nouns[BASKET_OF_EGGS] = Noun("BASKET OF EGGS", "Someone must have forgotten these. They look fresh.", BASKET_OF_EGGS, NONE, true);
    nouns[DOG_BONE] = Noun("DOG BONE", "A dog must had hidden this here. It's a bit chewed up.", DOG_BONE, NONE,  true);
    nouns[NEWS_PAPER] = Noun("NEWS PAPER", "A newspaper with the headline 'Mayor's approval rating at an all time high despite the scandal'.", NEWS_PAPER, NONE, true);
    nouns[LOST_RING] = Noun("LOST RING", "Looks like it is a wedding ring. I hope the owner finds it.",  LOST_RING, NONE, true);
    nouns[WATERING_CAN] = Noun("WATERING CAN", "This watering can looks like it's been used a lot.", WATERING_CAN, NONE, true);
    nouns[COIN_PURSE] = Noun("COIN PURSE", "An emerald green coin purse. It's empty.", COIN_PURSE, NONE, true);
    nouns[LOVE_POTION] = Noun("LOVE POTION", "A small vial with a rose colored liquid. Looks like someone changed their mind.", LOVE_POTION, NONE, true);
    nouns[FLYER] = Noun("FLYER", "A flyer from the adventurers guild. It shows a quest to clear out the goblins in the forest.", FLYER, NONE, true);
    nouns[CHEESE_WHEEL] = Noun("CHEESE WHEEL", "You are not entirely sure how this got here, or why it is here.\nIt has a slice missing, and small crumbs trailing from the missing piece.", CHEESE_WHEEL, NONE, true);
    nouns[RUBY] = Noun("RUBY", "A small ruby, it might have been part of a necklace, ring, or came from a vase.", RUBY, NONE, true);
    nouns[DAGGER] = Noun("DAGGER", "A small dagger it looks like it was hidden here. It's sharp.", DAGGER, NONE, true);
    nouns[COCONUT_PIECES] = Noun("COCONUT PIECES", "What are these doing out of the stables!", COCONUT_PIECES, NONE, true);
    
    
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

void inventory (vector<Noun>& nouns)
{
    cout << "You are carrying: \n";
    for (int i = 0; i < NOUNS; i++)
    {
        if(nouns[i].location == NONE)
        {
            cout << nouns[i].word << '\n';
        }
    }
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
        cout << "You flip the coin and catch it. It's heads. On the heads side there seems to be the founder's face.\n";
    }
    else if(noun == EMPTY_ALE_BOTTLE)
    {
        cout << "You look inside the bottle for a last drop. There is nothing left, but it does have a floral smell. This bottle seems to be reuseable.\n";
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
        cout << "You try on the ring. It's too small to fit your fingers.\n";
    }
    else if(noun == WATERING_CAN)
    {
        cout << "You fill up the watering can, and water a dying plant.\n";
    }
    else if(noun == COIN_PURSE)
    {
        cout << "You feel the material. It is velvety. It seems like something that would belong to an elderly person.\n";
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
        cout << "You roll the cheese wheel. It still rolls just fine despite the missing piece.\n";
    }
    else if(noun == RUBY)
    {
        cout << "You look at the ruby in the sunlight. It sparkles.\n";
    }
    else if(noun == DAGGER)
    {
        cout << "You cut a piece of bread with it. Yep it is sharp! When cutting the bread runes on the blade started to glow.\n";
    }
    else if(noun == COCONUT_PIECES)
    {
        cout << "You smell the coconut pieces. They smell nice.\n";
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
            cout << "This coin looks very old, it might be worth while to put it somewhere it can be displayed. Maybe Town Hall would know?\n";
        }
        else if(noun == EMPTY_ALE_BOTTLE)
        {
            cout << "Bottles can be reused if cleaned properly. Is there a place that would reuse ale bottles?\n";
        }
        else if(noun == BASKET_OF_EGGS)
        {
            cout << "There are a mix of brown, and white eggs. The basket has the smell of yeast, was it used to cover bread while it rises?\n";
        }
        else if(noun == DOG_BONE)
        {
            cout << "The bone looks like it was once part of a femur. You don't really see any dogs around the villagers homes but you did notice one in the garden next to the village homes.\n";
        }
        else if(noun == NEWS_PAPER)
        {
            cout << "The headline reads 'Mayor's approval rating at an all time high despite the scandal'. The mayor might need to know about this headline if he doesn't know already.\n";
        }
        else if(noun == LOST_RING)
        {
            cout << "The ring looks like a wedding ring. It's gold with a small diamond. Maybe someone who sells jewelery at the shopping center would know who it belongs to?\n";
        }
        else if(noun == WATERING_CAN)
        {
            cout << "The watering can is rusted, and leaves an ashy residue as you touch it. It might belong to a blacksmith?\n";
        }
        else if(noun == COIN_PURSE)
        {
            cout << "The coin purse is emerald green with floral embroidery and empty. Maybe it was dropped after a shopping trip?\n";
        }
        else if(noun == LOVE_POTION)
        {
            cout << "The vial has a pink glow, and smells like vanilla. You see a label on it that says 'The Black Cat Apothecary'.\n";
        }
        else if(noun == FLYER)
        {
            cout << "The flyer is from the adventurers guild. It shows a quest to kill a troll that is troubling a nearby village.\n";
        }
        else if(noun == CHEESE_WHEEL)
        {
            cout << "The cheese wheel has a slice missing, but it still looks edible and fresh. Maybe someone would like to have it as a meal? Maybe you can take it to the houses?\n";
        }
        else if(noun == RUBY)
        {
            cout << "The ruby is small and might have been part of some sort of jewelery. You have heard that the forge has jewelery made there, maybe that would be a good place to take it?\n";
        }
        else if(noun == DAGGER)
        {
            cout << "The dagger looks ornate and it has strong magical properties. It might be worth looking at the more magical places in town?\n";
        }
        else if (noun == COCONUT_PIECES)
        {
            cout << "The coconut pieces are in large pieces, and smell wonderful. You have heard that the horses like coconut.\n";
        }
    }
    else
    {
        cout << "There isn't anything like that here.\n";
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
        }
        else if (loc == ADVENTURERS_GUILD && noun == FLYER)
        {
            cout << "The guildmaster is curious about how a flyer ended up outside when the quest wasn't assigned, but is thankful to have it be returned.\n";
            nouns[FLYER].location = NONE;
            nouns[FLYER].location = ADVENTURERS_GUILD;
            nouns[FLYER].canBeFound = false;
        }
        else if (loc == TOWN_HALL && noun == OLD_COIN)
        {
            cout << "You discover that this coin is a valuable piece of history. It will be displayed at the town hall.\n";
            nouns[OLD_COIN].location = NONE;
            nouns[OLD_COIN].location = TOWN_HALL;
            nouns[OLD_COIN].canBeFound = false;
        }
        else if (loc == VILLAGERS_HOUSES && noun == CHEESE_WHEEL)
        {
            cout << "There is a starving child who takes the cheese wheel and gives it to his family. The family is grateful.\n";
            nouns[CHEESE_WHEEL].location = NONE;
            nouns[CHEESE_WHEEL].location = VILLAGERS_HOUSES;
            nouns[CHEESE_WHEEL].canBeFound = false;
        }
        else if (loc == SHOPPING_CENTER && noun == LOST_RING)
        {
            cout << "The shopkeeper is surprised that you have such an important ring. She is suspicious of how you got it.\n";
            nouns[LOST_RING].location = NONE;
            nouns[LOST_RING].location = SHOPPING_CENTER;
            nouns[LOST_RING].canBeFound = false;
        }
        else if (loc == SMALL_VILLAGE_GARDEN && noun == DOG_BONE)
        {
            cout << "There is a stray dog next to the garden who begs for food everyday. You give the dog the bone as a treat, and give the dog many pets.\n";
            nouns[DOG_BONE].location = NONE;
            nouns[DOG_BONE].location = BAKERY;
            nouns[DOG_BONE].canBeFound = false;
        }
        else if (loc == BAKERY && noun == BASKET_OF_EGGS)
        {
            cout << "The baker is embarrassed that he left the eggs outside. He was in a hurry and must have left them behind. He thanks you profusely.\n";
            nouns[BASKET_OF_EGGS].location = NONE;
            nouns[BASKET_OF_EGGS].location = BAKERY;
            nouns[BASKET_OF_EGGS].canBeFound = false;
        }
        else if (loc == FORGE && noun == WATERING_CAN)
        {
            cout << "The dwarf at the forge laughs, and says he must have left it behind when he was doing errands. He thanks you for returning it.\n";
            nouns[WATERING_CAN].location = NONE;
            nouns[WATERING_CAN].location = FORGE;
            nouns[WATERING_CAN].canBeFound = false;
        }
        else if (loc == SHOPPING_CENTER && noun == COIN_PURSE)
        {
            cout << "You see an elderly woman who is frantically looking for her coin purse. She is so grateful to have it back.\n";
            nouns[COIN_PURSE].location = NONE;
            nouns[COIN_PURSE].location = SHOPPING_CENTER;
            nouns[COIN_PURSE].canBeFound = false;
        }
        else if (loc == STABLES && noun == COCONUT_PIECES)
        {
            cout << "The horses take the pieces of coconut and eat them happily. You think you may have made some new friends.\n";
            nouns[COCONUT_PIECES].location = NONE;
            nouns[COCONUT_PIECES].location = STABLES;
            nouns[COCONUT_PIECES].canBeFound = false;
        }
        else if (loc == BROKEN_FOUNTAIN && noun == DAGGER)
        {
            cout << "You put the dagger on the fountain and glowing lights appear around you. Its the fae! They thank you for returning the dagger.\n";
            nouns[DAGGER].location = NONE;
            nouns[DAGGER].location = BROKEN_FOUNTAIN;
            nouns[DAGGER].canBeFound = false;
        }
        else if (loc == FORGE && noun == RUBY)
        {
            cout << "The blacksmith's wife who is a jeweler laughs and says that she remembers this ruby, and she will fix its owners necklace. She thanks you.\n";
            nouns[RUBY].location = NONE;
            nouns[RUBY].location = FORGE;
            nouns[RUBY].canBeFound = false;
        }
        else if (loc == MAYORS_HOME && noun == NEWS_PAPER)
        {
            cout << "The mayor seems upset about the headline, and he asks you if you know anything about the scandal. You tell him you don't. He is relieved.\n";
            nouns[NEWS_PAPER].location = NONE;
            nouns[NEWS_PAPER].location = MAYORS_HOME;
            nouns[NEWS_PAPER].canBeFound = false;
        }
        else if (loc == APOTHECARY && noun == LOVE_POTION)
        {
            cout << "Ceilia is happy to have the valuable love potion returned, but she is pretty secretive about who had purchased it in the first place.\n";
            nouns[LOVE_POTION].location = NONE;
            nouns[LOVE_POTION].location = APOTHECARY;
            nouns[LOVE_POTION].canBeFound = false;
        }
            nouns[noun].location = loc;
    }
    else
    {
        cout << "You can't exchange that here.\n";
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
                    cout << "The door is now open. You can see a lot of old untouched wine bottles. There's a layer of dust on each bottle.\n";
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
    while(word_1 != "QUIT")
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
    
    
