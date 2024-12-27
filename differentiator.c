#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef struct NodeType node;

struct NodeType{

  float coeff;
  node* next;

};

void addNode(node** L, float val);
int determineDegree(node* L);
void displayPolynomial(node* L);
node* requestPolynomial(void);
node* differentiate(node* L);

int main(void){

  node* f;

  f = requestPolynomial();

  printf("The polynomial you entered is:\nf(x) = ");

  displayPolynomial(f);

  printf("The derivative of f is:\nf'(x) = ");

  displayPolynomial(differentiate(f));

  printf("\n");

  return 0;

}

void addNode(node** L, float val){

  node* p;
  node* new = (node *) malloc(sizeof(node));

  new -> coeff = val;

  new -> next = NULL;

  if (*L == NULL){

    *L = new;
    return;

  }

  for (p = *L; p -> next != NULL; p = p -> next);

  p -> next = new;

}

int determineDegree(node* L){

  int degree = -1;

  for (node* p = L; p != NULL; p = p -> next) degree++;

  return degree;

}

void displayPolynomial(node* L){

  int degree_poly = determineDegree(L);
  int current_deg = degree_poly;

  if (degree_poly == 0){

    printf("%.2f\n", L -> coeff);
    return;

  }
  else if (degree_poly == 1){

    float constant = (L -> next) -> coeff;

    if (constant == 0) printf("%.2fx\n", L -> coeff);
    else if (constant < 0) printf("%.2fx - %.2f\n", L -> coeff, fabs(constant));
    else printf("%.2fx + %.2f\n", L -> coeff, constant);

    return;

  }

  for (node* p = L; p != NULL; p = p -> next){

    float curr_coeff = p -> coeff;

    if (current_deg == degree_poly){

      if (curr_coeff == 1) printf("x^%d", current_deg);
      else if (curr_coeff == -1) printf("-x^%d", current_deg);
      else printf("%.2fx^%d", curr_coeff, current_deg);

    }
    else if (current_deg == 1){

      if (curr_coeff > 0){

        if (curr_coeff == 1) printf(" + x");
        else printf(" + %.2fx", curr_coeff);

      }
      else if (curr_coeff < 0){

        if (curr_coeff == - 1) printf(" - x");
        else printf(" - %.2fx", fabs(curr_coeff));

      }

    }
    else if (current_deg == 0){

      if (curr_coeff > 0) printf(" + %.2f\n", curr_coeff);
      else if (curr_coeff < 0) printf(" - %.2f\n", fabs(curr_coeff));

    }
    else{

      if (curr_coeff > 0){

        if (curr_coeff == 1) printf(" + x^%d", current_deg);
        else printf(" + %.2fx^%d", curr_coeff, current_deg);

      }
      else if (curr_coeff < 0){

        if (curr_coeff == - 1) printf(" - x^%d", current_deg);
        else printf(" - %.2fx^%d", fabs(curr_coeff), current_deg);

      }

    }

    current_deg--;
  }

}

node* requestPolynomial(void){

  node* p = NULL;
  float curr_coeff;

  printf("Enter a polynomial by providing coefficients: ");

  while (scanf("%f", &curr_coeff) != EOF) addNode(&p, curr_coeff);

  printf("\n");

  return p;

}

node* differentiate(node* L){

  int current_deg = determineDegree(L);

  if (current_deg == 0){

    node* p = (node *) malloc(sizeof(node));

    p -> coeff = 0;

    p -> next = NULL;

    return p;

  }

  node* p = NULL;

  for (node* k = L; k -> next != NULL; k = k -> next){

    float new_coeff = current_deg * (k -> coeff);

    addNode(&p, new_coeff);

    current_deg--;
  }

  return p;

}