#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define ALPHABET_SIZE 26

struct trie
{
    char value;
    struct trie *children[ALPHABET_SIZE];
    bool end_of_key;
};

struct trie *trie_create(char value);//
struct trie *trie_insert(struct trie *root, char *key);
void trie_lookup(struct trie *root, char *key);//what return?
struct trie *trie_delete(struct trie *root, char *key);//do we need to delete a word or a node?
void trie_print(struct trie *root);//level?

struct trie *trie_create(char value)
{
    struct trie *node = malloc(sizeof(struct trie));
    for (int i = 0; i < ALPHABET_SIZE; i++)
        node->children[i] = NULL;
    node->end_of_key = 0;
    node->value = value;
    return node;
}

struct trie *trie_insert(struct trie *root, char *key)
{
    struct trie *temp = root;

    for (int i = 0; key[i] != '\0'; i++)
    {
        int index = key[i] - 'a';
        if (temp->children[index] == NULL)
        {
            temp->children[index] = trie_create(key[i]);
        }
        temp = temp->children[index];
    }
    temp->end_of_key = true;
    return root;
}

void trie_lookup(struct trie *root, char *key)
{
    struct trie *temp = root;

    for (int i = 0; key[i] != '\0'; i++)
    {
        int position = key[i] - 'a';
        if (temp->children[position] == NULL)
            printf("The word %s is not found!\n", key);
        temp = temp->children[position];
    }
    if (temp != NULL && temp->end_of_key == 1)
    {
        printf("The word %s is found!\n", key);
    }
    else
    {
        printf("The word %s is not found!\n", key);
    }
}

void trie_print(struct trie *root)
{
    if (!root)
        return;
    struct trie *temp = root;
    printf("%c -> ", temp->value);
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        trie_print(temp->children[i]);
    }
}

int main()
{
    struct trie *root = trie_create('\0');
    
    root = trie_insert(root, "hello");
    root = trie_insert(root, "hi");
    root = trie_insert(root, "teabag");
    root = trie_insert(root, "teacan");

    trie_lookup(root, "tea");
    trie_lookup(root, "teabag");
    trie_lookup(root, "teacan");
    trie_lookup(root, "hi");
    trie_lookup(root, "hey");
    trie_lookup(root, "hello");

    trie_print(root);
    return 0;
}
