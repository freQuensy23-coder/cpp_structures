#include <cstddef>
#include<iostream>

using namespace std;

struct subforwardlist {
    int data;
    subforwardlist *next;
};


bool init(subforwardlist **s_list) {
    *s_list = nullptr;
    return true;
}

void clear(subforwardlist **s_list) {
    if (*s_list == nullptr) {
        return;
    }
    if ((**s_list).next == nullptr) {
        delete *s_list;
        *s_list = nullptr;
        return;
    }
    clear(&(**s_list).next);
    delete *s_list;
    *s_list = nullptr;
}

bool init_with_one(subforwardlist **s_list) {
    (**s_list).next = nullptr;
    (**s_list).data = 0;
    return true;
}
				
bool push_back(subforwardlist **s_list, int d) {
    if (*s_list == nullptr) {
        auto *new_s_list = new subforwardlist;
        init_with_one(&new_s_list);
        new_s_list->data = d;
        *s_list = new_s_list;
        return true;
    }
    if ((**s_list).next != nullptr) {
        auto next = (**s_list).next;
        push_back(&next, d);
    } else {
        auto *new_s_list = new subforwardlist;
        init_with_one(&new_s_list);
        new_s_list->data = d;
        (**s_list).next = new_s_list;
    }
    return true;
}

int pop_back(subforwardlist **s_list) {
    if (*s_list == nullptr) {
        return 0;
    }
    if ((**s_list).next == nullptr) {
        int res = (**s_list).data;
        delete *s_list;
        *s_list = nullptr;
        return res;
    } else {
        return pop_back(&(**s_list).next);
    }
}

bool push_forward(subforwardlist **s_list, int d) {
    auto *new_s_list = new subforwardlist;
    init_with_one(&new_s_list);
    new_s_list->data = d;
    new_s_list->next = *s_list;
    *s_list = new_s_list;
    return true;
}

int pop_forward(subforwardlist **s_list) {
    if (*s_list == nullptr) {
        return 0;
    }
    int res = (**s_list).data;
    auto * new_s_list = (**s_list).next;
    delete *s_list;
    *s_list = new_s_list;
    return res;
}

bool push_where(subforwardlist **s_list, unsigned int i, int d) {
    if (i == 0) {
        return push_forward(s_list, d);
    }
    return push_where(&(**s_list).next, i - 1, d);
}

int erase_where(subforwardlist **s_list, unsigned int i) {
    if (i == 0) {
        return pop_forward(s_list);
    } else {
        return erase_where(&(**s_list).next, i - 1);
    }
}

unsigned int size(subforwardlist **s_list) {
    if (*s_list == nullptr) {
        return 0;
    }
    if ((**s_list).next == nullptr) {
        return 1;
    }
    return 1 + size(&(**s_list).next);
}


