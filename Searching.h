#include "Utility.h"
#include "List.h"

typedef int Key; 
typedef int Record;


//Definition of a Key class: 
class Key{
    int key;
public:
    static int comparisons; 
    Key (int x = 0);
    int the_key( ) const;
};

bool operator == (const Key &x, const Key &y);
bool operator > (const Key &x, const Key &y);
bool operator < (const Key &x, const Key &y);
bool operator >= (const Key &x, const Key &y);
bool operator <= (const Key &x, const Key &y);
bool operator != (const Key &x, const Key &y);

bool operator == (const Key &x, const Key &y) {
    Key::comparisons++;
    return x.the_key()== y.the_key(); 
}

// Definition of a Record class: 
class Record{
public:
operator Key(); 
// implicit conversion from Record to Key.
// Add any constructors and methods for Record objects. private:
// Add data components. 
};

Error_code sequential_search(const List<Record> &the_list, const Key &target, int &position)
/* Post: If an entry in the_list has key equal to target, then return success and the output parameter position locates such an entry within the list. Otherwise return not_present and position becomes invalid. */
{
    int s = the_list.size();
    for (position = 0; position < s; position++) {
        Record data; 
        the_list.retrieve(position, data); 
        if (data == target) return success;
    }
    return not_present;
}