#ifndef _ZCFG_LIST_H
#define _ZCFG_LIST_H

struct list_head {
        struct list_head *next, *prev;
};

#define LIST_HEAD_INIT(name) { &(name), &(name) }

#define LIST_HEAD(name) \
        struct list_head name = LIST_HEAD_INIT(name)

static inline void INIT_LIST_HEAD(struct list_head *list)
{
        list->next = list;
        list->prev = list;
}

static inline void __list_add(struct list_head *new,
                              struct list_head *prev,
                              struct list_head *next)
{
        next->prev = new;
        new->next = next;
        new->prev = prev;
        prev->next = new;
}

static inline void list_add(struct list_head *new, struct list_head *head)
{
        __list_add(new, head, head->next);
}

static inline void __list_del(struct list_head * prev, struct list_head * next)
{
		next->prev = prev;
		prev->next = next;
}

#define LIST_POISON1  ((void *) 0x00100100)
#define LIST_POISON2  ((void *) 0x00200200)

static inline void list_del(struct list_head *entry)
{
		__list_del(entry->prev, entry->next);
		entry->next = (struct list_head*)LIST_POISON1;
		entry->prev = (struct list_head*)LIST_POISON2;
}

#define container_of(ptr, type, member) ({                      \
        const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
        (type *)( (char *)__mptr - offsetof(type,member) );})

#define list_entry(ptr, type, member) \
        container_of(ptr, type, member)

#define list_for_each_entry(pos, head, member)                         \
        for (pos = list_entry((head)->next, typeof(*pos), member);     \
             &pos->member != (head);                                    \
             pos = list_entry(pos->member.next, typeof(*pos), member))

#define list_for_each_entry2(pos, head, member)                         \
        for (pos = list_entry((head)->prev, typeof(*pos), member);     \
             &pos->member != (head);                                    \
             pos = list_entry(pos->member.prev, typeof(*pos), member))

#define list_for_each_entry_from(pos, head, member)                         \
        for (;     \
             &pos->member != (head);                                    \
             pos = list_entry(pos->member.next, typeof(*pos), member))
			 
#define list_for_each_entry_safe(pos, n, head, member)			\
	for (pos = list_entry((head)->next, typeof(*pos), member),	\
		n = list_entry(pos->member.next, typeof(*pos), member);	\
	     &pos->member != (head); 					\
	     pos = n, n = list_entry(n->member.next, typeof(*n), member))
			 	 
#endif

