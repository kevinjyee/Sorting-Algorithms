/*
 * Project4.c
 *
 * My Name
 * My Section Time
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Set.h"
#include <stdint.h>
#include <assert.h>
#include <math.h>
//#define remove
#define mergesortinsert;
/*
 * Several of the required functions have been written already
 * You may use these functions as-is or you may modify them in any way.
 * Please NOTE, you are responsible for ensuring that the functions work correctly in
 * your project solution. Just because the function works correctly in my solution does
 * NOT mean that the function will work correctly in yours.
 */

/*
 * Design NOTES:
 *
 * The design provided in this starter kit assumes
 * (1) empty sets will be represented with length == 0 and elements == nullptr (i.e., address 0)
 * (2) amortized doubling is not used, and capacity is ignored/unused. Functions should assume that
 * the amount of storage available in the elements[] array is equal to length
 */



/* done for you already */
void destroySet(Set* self) {
	free(self->elements);
}

/* done for you already */
void createEmptySet(Set* self) {
	self->len = 0;
	self->elements = 0;
}

/* done for you already */
void createSingletonSet(Set* self, int x) {
	self->elements = (int*) malloc(sizeof(int));
	self->elements[0] = x;
	self->len = 1;
}

/* done for you already */
void createCopySet(Set* self, const Set* other) {
	self->elements = (int*) malloc(other->len * sizeof(int));
	for (int k = 0; k < other->len; k += 1) {
		self->elements[k] = other->elements[k];
	}
	self->len = other->len;
}


/* done for you already */
void assignSet(Set* self, const Set* other) {
	if (self == other) { return; }

	destroySet(self);
	createCopySet(self, other);
}

/*
 * Function: merge
 * ------------------------------------------
 * merge is the final step of merge sort that takes the leftmost array and combines it with the right most array
 *
 */
void merge(int32_t x1[], uint32_t leftlength,
		int32_t x2[], uint32_t rightlength,
		int32_t out[]) {
	int i = 0; // left increment
	int j = 0; // right increment
	int w = 0; // used to increment the "output array"

	while (i < leftlength && j < rightlength) {
		if (x1[i] < x2[j]) {
			/*if left[i] < right [j], that means left [i] goes in first*/

			out[w] = x1[i];
			i += 1;
		} else {
			/*right[j] can go in*/
			out[w] = x2[j];
			j += 1;
		}
		w += 1;
	}

	while (i < leftlength) {
		//the length of right has run out, put the remaining members of left[] in
		out[w] = x1[i];
		i += 1;
		w += 1;
	}

	while (j < rightlength) {
		//the lenght of left has run out, put the remaining members of right[] in
		out[w] = x2[j];
		j += 1;
		w += 1;
	}

}

/*
 * Function: mergeSort
 * -----------------------------------
 * basic merge sort using recursion
 * determines the middle of the array
 *
 */
void mergeSort(int32_t x[], uint32_t n) {

	/*
	 * n contains length of x
	 * mid <- n/2
	 * Left = x
	 * Right = x + n/2
	 * Continue until n < 2
	 *
	 */

	int32_t* Left = x;
	int32_t* Right = x+n/2;

	if (n < 2) { return; }

	mergeSort(Left, n / 2);
	mergeSort(Right, n - n / 2);

	int32_t* tmp = (int32_t*) malloc(n * sizeof(int32_t));
	merge(Left, n / 2, Right , n - n / 2, tmp);

	for (int k = 0; k < n; k += 1) {
		x[k] = tmp[k]; //puts the values of the tmp array back into x[k]
	}
	free(tmp);

}

/*
 * Function: insertionSort
 * ------------------------------------
 * basic insertion sort algorithm
 * Starting at the end of the array, loop until x < self elements[k]
 */

void insertionSort(Set* self, int32_t x){
	int k = self->len-1;

		//Insertion sort algorithm
		while(x < self->elements[k] && k >=0){
			self->elements[k+1] = self->elements[k];
			k--;
		}
		self->elements[k+1] = x;
}
/*
 * Function: binarySearch
 * ------------------------------------
 * return the index of the searchvalue
 * splits the array into two halves to look for the value
 */

#ifdef binarySearch
int binarySearch(const Set* self, int32_t searchvalue) {
	if (self->len == 0) { return -1; } // special case for empty arrays
	// n is length or array
	// searchvalue is the element we're looking for

	uint32_t start = 0;
	uint32_t end = self->len;


	while (start < end - 1) { // while x[lo, hi) contains more than one element
		uint32_t mid = (start + end) / 2; // midpoint

		 if (searchvalue < self->elements[mid]) { // searchvalue must be in x[lo, m)
			end = mid;
		} else { // searchvalue must be in x[m, hi)
			start = mid;
		}
	}

	if(searchvalue == self->elements[start]){
		return start;
	}
	else{
		return -1;
	}
}


#endif


int binarySearch(const Set* self, int32_t searchvalue){
	uint32_t start =0;
	uint32_t end = self->len;

	while(start<end-1){
		uint32_t mid = (start+end)/2;

		if(searchvalue < self->elements[mid]){
			end = mid;
		}
		else{
			start = mid;
		}

	}
	if(searchvalue == self->elements[start]){
		return start;
	}
	else{ return -1;}
}
/*Function: createSetFromArray
 * ----------------------------------------------------------
 *  construct a set using the first n values of the array
 * Note that the array may or may not already be sorted. Regardless of the
 * ordering of the array, you must construct the set properly (satisfying
 * all design invariant properties for your set).
 * you can assume n >= 0, and n is small enough that we won't run out of memory
 * do not change the elements in the array in any way
 * // elements of the array (i.e,. from array[0] to array[n-1])
						// NOTE: the array may not be sorted, you must ensure that you correctly
						// construct the new set regardless of the order elements appear in array
						// do NOT change the array
						// this function must run in time complexity no worse than O(n log n) -- HINT mergesort
 */
void createSetFromArray(Set* self, const int32_t array[], uint32_t n) {
	int i = 0;
	self->elements = (int*) malloc(n* sizeof(int));
	self->len = n;
	/* Put values from array in the set */

	for(i=0; i < n; i++){
		self->elements[i] = array[i];
	}

	/*Sort elements*/
	mergeSort(&self->elements[0], self->len);
}


/*
 * Function: isMemberSet
 * ------------------------------------------------------
 *  return true if x is an element of self */

bool isMemberSet(const Set* self, int x) {

	/*Using Binary Search, determine if x is an element of the set*/
	int value;

	if((value = binarySearch(self, x)) != -1){
		return true;
	}
	else{
		return false;
	}
}



/*Function: insertSet
 * ------------------------------
 * add x as a new member to this set.
 * If x is already a member, then self should not be changed
 * Be sure to restore the design invariant property that elemnts[] remains sorted
 * (yes, you can assume it is sorted when the function is called, that's what an invariant is all about)
 */

void insertSet(Set* self, int x) {
	//Outlier case. If the set is empty, make a set
	if (self->len == 0){
	createSingletonSet(self, x);
		}
	//Outlier case. If x already exists, then return
	if(isMemberSet(self, x)){return;};

	//allocate temporary memory space that is 1 greater in size than the current length
	int* temp = (int*) malloc((self->len + 1)*(sizeof(int)));

	int i =0;
	for(int i=0; i<self->len; i++){
	//put all values of the elements into the temporary memory
		temp[i] = self->elements[i];
	}

//	temp[self->len] = x;// update the last element of the temporary memory to the values you want to add
	free(self->elements);//free the current elements
	self->elements= temp;//passing the address of the element pointers to the temp memory we recreated
	//mergeSort(self->elements,self->len); // sort the array (Decided insertion sort would've been faster)
	insertionSort(self,x);
	self->len = self->len + 1; // update the lenght of the memory


}




/*Function: removeSet
 * -----------------------------
 * don't forget: it is OK to try to remove an element
 * that is NOT in the set.
 * If 'x' is not in the set 'self', then
 * removeSet should do nothing (it's not an error)
 * Otherwise, ('x' IS in the set), remove x. Be sure to update self->length
 * It is not necessary (nor recommended) to call malloc -- if removing an element means the
 * array on the heap is "too big", that's almost certainly OK, and reallocating a smaller array
 * is almost definitely NOT worth the trouble
 */

void removeSet(Set* self, int x) {
	/*Determine index of x to remove*/

	/*Find index using binary search*/

	int index = binarySearch(self, x);

	if(index == -1 | self->len == 0){
		return; // if not found then return
	}
	int k =0; // when found, remove the index
		for(k = index; k < self->len -1; k++){
			self->elements[k] = self->elements[k+1];
		}
		self->len -= 1;

}





/* done for you already */
void displaySet(const Set* self) {
	int k;

	printf("{");

	if (self->len == 0) {
		printf("}");
	}
	else {
		for (k = 0; k < self->len; k += 1) {
			if (k < self->len - 1) {
				printf("%d,", self->elements[k]);
			} else {
				printf("%d}", self->elements[k]);
			}
		}
	}
}


/* Function: isEqualtoSet
 * --------------------------------------------------
 * return true if self and other have exactly the same elements */
bool isEqualToSet(const Set* self, const Set* other) {
	/* First compare lengths to see if they're equal*/
	if(self->len != other->len){
		return false;
	}
	int i =0;
	for(i=0; i<self->len; i++){
		if(self->elements[i] != other->elements[i]){
			return false;
		}
	}
	return true;
}




/*Function: isSubetOf
 * --------------------------------
 *  return true if every element of self is also an element of other */

bool isSubsetOf(const Set* self, const Set* other) {
	if (self->len > other->len) return false;

	int i = 0;
	int j = 0;
	for (i=0; i < self->len; i++) {
		do  {
			if (self->elements[i] == other->elements[j]) break;
			if (other->elements[j] > self->elements[i]) return false;
			j++;
			if (j == other->len) return false;
		}while(true);
	}
	return true;
}

/* done for you */
bool isEmptySet(const Set* self) {
	return self->len == 0;
}



/* Function: intersectFromSet
 * --------------------------------------
 * remove all elements from self that are not also elements of other */
void intersectFromSet(Set* self, const Set* other) {

	int i = 0, j = 0, k = 0;
	int* tmp = (int*) malloc(self->len * sizeof(int));

		 while ((j < self->len) && (k < other->len)) {
		             if (self->elements[j] < other->elements[k]) {
		                 j++;
		             } else if (self->elements[j] > other->elements[k]) {
		                 k++;
		             } else {
		                 //Neither greater or less than elements in other
		            	 //That means it exists in others
		            	 //Put these values into the tmp array


		                 tmp[i++] = self->elements[j];
		                 j++;
		                 k++;
		             }
		         }
		 free(self->elements);
		     self->elements = tmp;
		     self->len = i;



}


/* remove all elements from self that are also elements of other */

void subtractFromSet(Set* self, const Set* other){
	int i=0, j=0, k=0;
	int* tmp = (int*) malloc(self->len * sizeof(int));


		 /*
		  * If other runs out that means everything in self can stay
		  */
		 while(j<self->len){
			 /*search through entire self array*/



		if(other->len == 0){
			/*outlier for if the other array is 0*/
			return;
		}
		 if(k >= other->len){
			 /*Elements of other has been exhausted, the rest of the elements won't exist*/
			 tmp[i] = self->elements[j];
			 i+=1;
			 j+=1;
	 }
		 else if(self->elements[j] < other->elements[k]){
			 /*if self[j] is less than elements[k]
			  * There is no way self[j] will be in other[k]
			  * add this item to the tmp array
			  */

			 tmp[i] = self->elements[j];
			 j+=1;
			 i+=1;
		 }
		 else if(self->elements[j] > other->elements[k]){
			 /*if elements in j is greater than elements in k
			  * Tells us nothing
			  * increment k to catch up to j values
			  */
			 k+=1;
		 }
		 else{
			 /*it is neither greater or less than the value we are searching for
			  * go to next value
			  */
			 j+=1;
			 k+=1;
		 }
		 }

		 free(self->elements);
		     self->elements = tmp;
		     self->len = i;

}

/* add all elements of other to self (obviously, without creating duplicate elements) */
void unionInSet(Set* self, const Set* other) {
	int binaryflag = 0;

	if(self->len + other->len < self->len * log(other->len)){
		binaryflag = 1;
	}

	/*Add all elements of other to self (not repeating the duplicate*/
	/*Must retain order*/

	if(binaryflag == 1){
		  int i = 0, j = 0, k = 0;
		  int* tmp = (int*) malloc((self->len+other->len) * sizeof(int));

		  while(k<other->len || j<self->len){
			  /*When other is exhausted, and self is not, make sure to put the elements of self back in*/

			  if(j>=self->len){
				  /*If the elements of self is exhausted, that means the rest of other can go in without checking*/

				  tmp[i] = other->elements[k];
				  i+=1;
				  k+=1;

			  }
			  else if (k>=other->len){
				  /*If the elements of other is exhausted, that means the rest of self can go in without checking*/

				  tmp[i] = self->elements[j];
				  i+=1;
				  j+=1;

			  }

			  else if(other->elements[k] < self->elements[j]){
				  /*If elements of other is less than elements in self, there is no way other is in self
				   * so we add it into our tmp array
				   */

				  tmp[i] = other->elements[k];
				  i++;
				  k++;
			  }
			  else if(other->elements[k] > self->elements[j]){
				  /* If elements of other is greater than the elements of self,
				   * that tells us that self should go in because it is less than other
				   * increment j so we can determine the comparison of the next two values
				   */
				 tmp[i] = self->elements[j];
				 i++;
				 j++;
			  }
			  else{
				  /*this means that they matched completely*/
				  tmp[i] = self->elements[j];
				  i++;
				  j++;
				  k++;
			  }
		  }
		  free(self->elements);
		 		     self->elements = tmp;
		 		     self->len = i;

		}




	if(binaryflag == 0){
/*This function runs at nlog(m)*/
int temp = other->len -1;
while(temp>=0){
	if(!(isMemberSet(self,other->elements[temp]))){
		insertSet(self,other->elements[temp]);
	}temp -=1;
}
	}
}




