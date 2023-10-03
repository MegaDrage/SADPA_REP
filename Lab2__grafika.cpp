#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <graphics.h>

using namespace std;

struct vertex 
{
    int data;
    vertex* left;
    vertex* right;
};

void f_rand(int arr[], int n);
void bypass_left_to_right(vertex *p);
void add_recurs(int D, vertex*& root);
void add_kosven(int D, vertex **root);
int size_of_tree(vertex *p);
int control_summ_of_tree(vertex *p);
int height_of_tree(vertex *p);
int summ_lenght_track(vertex *p, int L);
vertex* ISDP(int L, int R, int arr[]);
void QuickSort(int *A, int n);
void drawTree(vertex* node, int x, int y, int level, int horizontalSpacing);

int main() 
{
    
    int width = 1920;
    int height = 1080;
    initwindow(width, height);
    int n;
    cout << "Enter n: ";
    cin >> n;
    
    int A[n];
    f_rand(A, n);
    cout << endl;
    cout << "Random unique elements: ";
    for (int i = 0; i < n; i++) {
        cout << A[i] << " ";
    }
    cout << endl;
    
    vertex* root1 = NULL;
	for (int i = 0; i < n; i++) 
	{
        add_recurs(A[i], root1);
    }
    
    int startX = 900;
    int startY = 100;
    int horizontalSpacing = 400;
    
    drawTree(root1, startX, startY, 1, horizontalSpacing);
    getch();
    closegraph();
    
    cout << endl;
    cout << "Bypass_left_to_right(recurs): ";
    bypass_left_to_right(root1);
    cout << endl;
    
    vertex* root2 = NULL;
    for (int i = 0; i < n; i++) 
	{
        add_kosven(A[i], &root2);
    }
    cout << endl;
    cout << "Bypass_left_to_right(kosven): ";
    bypass_left_to_right(root2);
    cout << "\n\n";
    
    cout << "Size of tree = " << size_of_tree(root2) << endl;
	cout << endl;
	
	cout << "Control summ = " << control_summ_of_tree(root2) << endl;
	cout << endl;
	
	cout << "Height of tree = " << height_of_tree(root2) << endl;
	cout << endl;
	
	float mh = static_cast<float>(summ_lenght_track(root2, 1)) / static_cast<float>(size_of_tree(root2));
	cout << "Middle height of tree = " << mh << endl;
	
	QuickSort(A, n);
	cout << endl << "Sorted mas for ISDP" << endl;
	for (int i = 0; i < n; i++) 
	{
        cout << A[i] << " ";
    }
    cout << endl;
	
	
	vertex *root = ISDP(0, n - 1, A);
	cout << endl;
	
	cout << "Bypass from left to righ: ";
	bypass_left_to_right(root);
	cout << endl << endl;
	
	cout << "Size of tree = " << size_of_tree(root) << endl;
	cout << endl;
	
	cout << "Control summ = " << control_summ_of_tree(root) << endl;
	cout << endl;
	
	cout << "Height of tree = " << height_of_tree(root) << endl;
	cout << endl;
	
	
	mh = static_cast<float>(summ_lenght_track(root, 1)) / static_cast<float>(size_of_tree(root));
	cout << "Middle height of tree = " << mh << endl;

    delete root1;
    delete root2;
    delete root;
    return 0;
}

void add_recurs(int D, vertex *&p) 
{
	if(p == NULL)
	{
		p = new vertex;
		p -> data = D;
		p -> left = NULL;
		p -> right = NULL;
	}
	else if(D < p -> data)
	{
		add_recurs(D, p->left);
	}
	else if(D > p -> data)
	{
		add_recurs(D, p->right);
	}
	else
	{
		return;
	}
}

void add_kosven(int D, vertex **root) 
{
    vertex **p = root;

    while (*p != nullptr) 
	{
        if (D < (*p)->data) 
		{
            p = &((*p)->left);
        } 
		else if (D > (*p)->data) 
		{
            p = &((*p)->right);
        } 
		else 
		{
            return;
        }
    }
    if(*p == NULL)
    {
    	(*p) = new vertex;
    	(*p) -> data = D;
		(*p) -> left = NULL;
		(*p) -> right = NULL;
	}
}

vertex* ISDP(int L, int R, int arr[])
{
	if(L>R)
	{
		return NULL;	
	} 
	else
	{
		int m = (L + R) / 2;
		vertex *p = new vertex;
		p -> data = arr[m];
		p -> left = ISDP(L, m - 1, arr);
		p -> right = ISDP(m + 1, R, arr);
		return p;
		
	}
}

void bypass_left_to_right(vertex *p)
{
	if(p != NULL)
	{
		bypass_left_to_right(p -> left);
		cout << p -> data << " ";
		bypass_left_to_right(p -> right);
	}
}

void f_rand(int arr[], int n) 
{
    vector<int> unique_values;
    for (int i = 1; i <= 100; i++) 
	{
        unique_values.push_back(i);
    }
    random_shuffle(unique_values.begin(), unique_values.end());

    for (int i = 0; i < n; i++) 
	{
        arr[i] = unique_values[i];
    }
}

int size_of_tree(vertex *p)
{
	int n = 0;
	if (p == NULL)
	{
		n = 0;
	}
	else
	{
		n = 1 + size_of_tree(p -> left) + size_of_tree(p -> right);
	}
	return n;
}

int control_summ_of_tree(vertex *p)
{
	int s = 0;
	if(p == NULL)
	{
		s = 0;
	}
	else
	{
		s = (p -> data) + control_summ_of_tree(p -> left) + control_summ_of_tree(p -> right); 
	}
	
	return s;
}

int height_of_tree(vertex *p)
{
	int h = 0;
	if(p == NULL)
	{
		h = 0;
	}
	else
	{
		h = 1 + max(height_of_tree(p -> left), height_of_tree(p -> right));
	}
	return h;
}

int summ_lenght_track(vertex *p, int L)
{
	int slt = 0;
	if(p == NULL)
	{
		slt = 0;
	}
	else
	{
		slt = L + summ_lenght_track(p -> left, L + 1) + summ_lenght_track(p -> right, L + 1);
	}
	return slt;
}

void QuickSort(int *A, int n) 
{
    
    int L = 0, R = n - 1, i = L, j = R;
    int x = A[L];
    while (i <= j) 
	{
        while (A[i] < x) 
		{
            i++; 
        }
       
        while (A[j] > x) 
		{
            j--;
        }
        
        if (i <= j) 
		{
            int temp = A[i];
            A[i] = A[j];
            A[j] = temp;
            i++;
            j--;
        }
    }
    if (L < j) 
	{
        QuickSort(A, j + 1);
    }
    if (i < R) 
	{
        QuickSort(&A[i], n - i);
    }
}

void drawTree(vertex* node, int x, int y, int level, int horizontalSpacing)
{
    if (node == nullptr)
        return;

    int radius = 15; // Радиус узла

    // Рисуем текущий узел
    circle(x, y, radius);
    char text[10]; // Выделяем буфер для текста (предполагая, что число не превышает 10 символов)
    sprintf(text, "%d", node->data); // Копируем целое число в текстовый буфер
    outtextxy(x - 10, y - 10, text); // Передаем текстовый буфер функции outtextxy

    // Рисуем связь с правым узлом (если есть)
    if (node->right != nullptr)
    {
        int rightX = x + horizontalSpacing;
        int rightY = y + 50;
        line(x, y, rightX, rightY);
        drawTree(node->right, rightX, rightY, level + 1, horizontalSpacing / 2);
    }

    // Рисуем связь с левым узлом (если есть)
    if (node->left != nullptr)
    {
        int leftX = x - horizontalSpacing;
        int leftY = y + 50;
        line(x, y, leftX, leftY);
        drawTree(node->left, leftX, leftY, level + 1, horizontalSpacing / 2);
    }
}
