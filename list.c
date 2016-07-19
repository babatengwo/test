/* 双向循环链表，带头指针 */
struct list_node
{
    struct list_node *prev, *next;
};

/* 初始化头指针 */
void list_init_head(struct list_node* head)
{
    head->prev = head->next = head;
}

/* 量表是否为空 是返回1，否返回0 */
int list_is_empty(const struct list_node* head)
{
    return (head->prev == head) && (head->next == head);
}

/* 链表遍历 */
#define list_for_each(iter, head) \
    for (iter = (head)->next; iter != (head); iter = iter->next)

/* 链表逆序遍历 */
#define list_for_each_reverse(iter, head) \
    for (iter = (head)->prev; iter != (head); iter = iter->prev)

/* 链表遍历，支持删除操作 */
#define list_for_each_remove(iter, n, head) \
    for (iter = (head)->next, n = iter->next; iter != (head); iter = n, n = iter->next)

/* 求包含此链表的结构体指针 */
#define list_entry(ptr, type, member) \
    ((type *)((char *)(ptr)-(unsigned long)(&((type *)0)->member)))

static void __list_insert(struct list_node* node, struct list_node* prev, struct list_node* next)
{
    prev->next = next->prev = node;
    node->prev = prev;
    node->next = next;
}

/* 插入头节点 */
void list_push_front(struct list_node* head, struct list_node* node)
{
    __list_insert(node, head, head->next);
}

/* 插入尾节点 */
void list_push_back(struct list_node* head, struct list_node* node)
{
    __list_insert(node, head->prev, head);
}

static void __list_delete(struct list_node* prev, struct list_node* next)
{
    prev->next = next;
    next->prev = prev;
}

/* 移除节点 */
void list_remove(struct list_node* node)
{
    __list_delete(node->prev, node->next);
    node->prev = node->next = NULL;
}

/* 链表接合 将list接合到head,新链表的头节点仍为head */
void list_splice(struct list_node* head, struct list_node* list)
{
    if (list_is_empty(list) == 0)
    {
        list->next->prev = head;
        head->prev = list->next;

        list->prev->next = head->next;
        head->next->prev = list->prev;
    }
}
