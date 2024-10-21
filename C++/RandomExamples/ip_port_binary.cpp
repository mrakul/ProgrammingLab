#include <utility>
#include <cstdint>
#include <cstdlib>

using namespace std;

using ip_port = pair<uint32_t, uint16_t>;

#define COUNTOF(arr) sizeof(arr) / sizeof(arr[0])

//template <typename T, typename U, typename Comparator>
template <typename T, typename Comparator>
static inline bool binary_search(const T tableToFind[], size_t table_size, const T value, Comparator comparator)
{
    int leftBound = 0;
    int rightBound = table_size - 1;

    if (comparator(tableToFind[rightBound], value) == 0)
        return true;

    while (leftBound <= rightBound)
    {
        int middle = (leftBound + rightBound) >> 1;

        if (comparator(tableToFind[middle], value) == 0)
            return true;

        if (comparator(tableToFind[middle], value) < 0)
            leftBound = middle + 1;
        else
            rightBound = middle - 1;
    }

    return false;
}


constexpr ip_port ip_port_db[] = 
{
    {0x0595fba5, 443},
    {0x0595fba5, 443},
    {0x0595fba6, 443},
    {0x0595fba6, 443},
    {0x0595fba7, 443},
    {0x0595fba8, 443},
    {0x0595fba8, 443},
    {0x0595fba9, 443},
    {0x0595fba9, 443},
};

static constexpr size_t ip_port_db_size = COUNTOF(ip_port_db);

int main(int argc, const char *argv[])
{
    auto ip_port_comparator = [](ip_port ip_port_db, ip_port ip_port_checked)
    {
        static constexpr int MOVE_LEFT_BOUND = -1;
        static constexpr int MOVE_RIGHT_BOUND = 1;

        if (ip_port_db.first < ip_port_checked.first) {
            return MOVE_LEFT_BOUND;
        }
        else if (ip_port_db.first > ip_port_checked.first) {
            return MOVE_RIGHT_BOUND;
        }
        // IPs are equal, check ports
        else if (ip_port_db.second < ip_port_checked.second) {
            return MOVE_LEFT_BOUND;
        }
        else if (ip_port_db.second > ip_port_checked.second) {
            return MOVE_RIGHT_BOUND;
        }
        // IP and port are equal
        else
            return EXIT_SUCCESS;
    };

    const auto ip_port_found = binary_search(ip_port_db, COUNTOF(ip_port_db), 
                                             std::pair<uint32_t, uint16_t>({0x0595fba6, 443}), ip_port_comparator);


    return ip_port_found;
}
