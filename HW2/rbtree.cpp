#include <iostream>
#include <string>

using namespace std;

struct node
{
    int key;
    string color;
    node* parent;
    node* left_child;
    node* right_child;
};

class RBT
{
public:
    node* root;
    node* nil;
    RBT()
    {
        nil = new node;
        nil->color = "black";
        nil->left_child = NULL;
        nil->right_child = NULL;
        root = nil;
    }

    void left_rotate(node*);
    void right_rotate(node*);
    void insertion(int);
    void insert_fixup(node*);
    void deletion(int);
    void deletion_fixup(node*);
    void transparent(node*, node*);
    node* successor(node*);
    void inorder(node*);
};

void RBT::transparent(node* transed, node* transing)
{
    if (transed->parent == nil) root = transing;
    else if (transed == transed->parent->left_child) transed->parent->left_child = transing;
    else transed->parent->right_child = transing;
    transing->parent = transed->parent;
}

void RBT::left_rotate(node* cur)
{
    node* y = cur->right_child;

    cur->right_child = y->left_child;
    if (y->left_child != nil) y->left_child->parent = cur;
    transparent(cur, y);
    y->left_child = cur;
    cur->parent = y;
}

void RBT::right_rotate(node* cur)
{
    node* y = cur->left_child;
    cur->left_child = y->right_child;

    if (y->right_child != nil) y->right_child->parent = cur;
    transparent(cur, y);
    y->right_child = cur;
    cur->parent = y;
}

void RBT::insertion(int key)
{
    node* y = nil;
    node* x = root;
    node* new_node = new node;

    new_node->key = key;
    while (x != nil)
    {
        y = x;
        if (x->key < new_node->key) x = x->right_child;
        else if (x->key > new_node->key) x = x->left_child;
        else return;
    }

    new_node->parent = y;
    if (y == nil) root = new_node;
    else if (new_node->key < y->key) y->left_child = new_node;
    else y->right_child = new_node;

    new_node->left_child = nil;
    new_node->right_child = nil;
    new_node->color = "red";

    if (new_node->parent == NULL) return;
    else if (new_node->parent->parent == NULL) return;

    insert_fixup(new_node);
}

void RBT::insert_fixup(node* cur)
{
    while (cur != root && cur->parent->color == "red")
    {
        if (cur->parent == cur->parent->parent->left_child)
        {
            node* y = cur->parent->parent->right_child;
            if (y->color == "red")
            {
                cur->parent->color = "black";
                y->color = "black";
                cur->parent->parent->color = "red";
                cur = cur->parent->parent;
            }

            else
            {
                if (cur == cur->parent->right_child)
                {
                    cur = cur->parent;
                    left_rotate(cur);
                }

                cur->parent->color = "black";
                cur->parent->parent->color = "red";
                right_rotate(cur->parent->parent);
            }

        }

        else if (cur->parent == cur->parent->parent->right_child)
        {
            node* y = cur->parent->parent->left_child;
            if (y->color == "red")
            {
                cur->parent->color = "black";
                y->color = "black";
                cur->parent->parent->color = "red";
                cur = cur->parent->parent;
            }

            else 
            {
                if (cur == cur->parent->left_child)
                {
                    cur = cur->parent;
                    right_rotate(cur);
                }

                cur->parent->color = "black";
                cur->parent->parent->color = "red";
                left_rotate(cur->parent->parent);
            }

        }
    }

    root->color = "black";
}

node* RBT::successor(node* s)
{
    s = s->right_child;
    while (s->left_child != nil) s = s->left_child;

    return s;
}

void RBT::deletion(int key)
{
    //find
    node* d_node = new node;
    d_node->key = key;
    node* x = root;

    while (x != nil)
    {
        if (x->key < d_node->key) x = x->right_child;
        else if (x->key > d_node->key) x = x->left_child;
        
        if (x->key == d_node->key) 
        {   
            d_node = x; 
            break; 
        }
    }
    if (x == nil) return;

    // delete
    x = new node;
    node* y = d_node;
    string origin_color = y->color;

    if (d_node->left_child == nil)
    {
        x = d_node->right_child;
        transparent(d_node, d_node->right_child);
    }
    else if (d_node->right_child == nil)
    {
        x = d_node->left_child;
        transparent(d_node, d_node->left_child);
    }

    else
    {
        y = successor(d_node);
        origin_color = y->color;
        x = y->right_child;

        if (y->parent == d_node) x->parent = y;
        else
        {
            transparent(y, y->right_child);
            y->right_child = d_node->right_child;
            y->right_child->parent = y;
        }

        transparent(d_node, y);
        y->left_child = d_node->left_child;
        y->left_child->parent = y;
        y->color = d_node->color;
    }

    if (origin_color == "black") deletion_fixup(x);
}

void RBT::deletion_fixup(node* cur)
{
    while (cur != root && cur->color == "black")
    {
        if (cur == cur->parent->left_child)
        {
            node* sil = cur->parent->right_child;
            if (sil->color == "red")
            {
                sil->color = "black";
                cur->parent->color = "red";
                left_rotate(cur->parent);
                
                sil = cur->parent->right_child;
            }

            if (sil->left_child->color == "black" && sil->right_child->color == "black")
            {
                sil->color = "red";
                cur = cur->parent;
            }

            else
            {
                if (sil->right_child->color == "black")
                {
                    sil->left_child->color = "black";
                    sil->color = "red";
                    right_rotate(sil);
                    sil = cur->parent->right_child;
                }

                sil->color = cur->parent->color;
                cur->parent->color = "black";
                sil->right_child->color = "black";
                left_rotate(cur->parent);
                cur = root;
            }

        }

        if (cur == cur->parent->right_child)
        {
            node* sil = cur->parent->left_child;
            if (sil->color == "red")
            {
                sil->color = "black";
                cur->parent->color = "red";
                right_rotate(cur->parent);

                sil = cur->parent->left_child;
            }

            if (sil->left_child->color == "black" && sil->right_child->color == "black")
            {
                sil->color = "red";
                cur = cur->parent;
            }

            else
            {
                if (sil->left_child->color == "black")
                {
                    sil->right_child->color = "black";
                    sil->color = "red";
                    left_rotate(sil);
                    sil = cur->parent->left_child;
                }

                sil->color = cur->parent->color;
                cur->parent->color = "black";
                sil->left_child->color = "black";
                right_rotate(cur->parent);
                cur = root;
            }
        }
    }

    cur->color = "black";
}

void RBT::inorder(node* cur)
{
    if(cur != nil)
    {
        inorder(cur->left_child);
        if(cur != root)
            cout << "key: " << cur->key << " parent: " << cur->parent->key << " color: " << cur->color << endl;
        else 
            cout << "key: " << cur->key << " parent: " <<  " " << " color: " << cur->color << endl;
        inorder(cur->right_child);
    }
}

int main() 
{
	
	int t;
    while (cin >> t)
    {
        RBT rbt;
        while (t--)
        {
            int ins, n;
            cin >> ins >> n;

            int* num = new int[n + 1];
            for (int i = 0; i < n; i++) cin >> num[i];

            if (ins == 1)
            {
                for (int i = 0; i < n; i++) rbt.insertion(num[i]);
             
                int print_check = 1;
                cout << "Insert: ";
                for (int i = 0; i < n; i++)
                {
                    if (print_check) cout << num[i], print_check = 0;
                    else cout << ", " << num[i];
                }
                cout << endl;
				rbt.inorder(rbt.root);
            }

			else if (ins == 2)
			{
				for (int i = 0; i < n; i++) rbt.deletion(num[i]);

				int print_check = 1;
				cout << "Delete: ";
				for (int i = 0; i < n; i++)
				{
					if (print_check) cout << num[i], print_check = 0;
					else cout << ", " << num[i];
				}
				cout << endl;
				rbt.inorder(rbt.root);
			}
        }
    }
	return 0;
}