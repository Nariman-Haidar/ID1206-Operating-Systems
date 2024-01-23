#include <stdlib.h>
#include <stdio.h>


// FCFS disk scheduling

int fcfs(int arr[], int head, int n){
	int mov, pos;
	int mov_count = 0;
	for (int i = 0; i < n; i++) {
        pos = arr[i];
        // calculate absolute distance
        mov = abs(pos - head);
        mov_count += mov;
        head = pos;
    }
	return mov_count;
}
// SSTF disk scheduling
int sstf(int arr[], int head, int n, int track_valid[]){
	int mov_count = 0;
	int track[n];
	int index = -1;
	
	int p;
	
	for(int j = 0; j < n; j++)
    {
	    p = arr[j];
	 	for(int i = 0; i < n; i++)
    	{
        	track[i] = abs(head - arr[i]);
    	} 
    	int min = 1e9;  
    	for(int k = 0; k < n; k++)
    	{
        	if (track_valid[k]== 0 && min > track[k])
        	{
            	min = track[k];
            	index = k;
        	}
    	}
		track_valid[index]= 1;
        mov_count += track[index];
        head = arr[index];
	 } 

	return mov_count;
}
//scan scheduling

int comparation (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

int scan(int arr[], int head, int n){
	int mov_count = 0;
	int j=0;
	int k=0;
	int pos, mov;
	
	qsort(arr, n, sizeof(int), comparation);
	
	int l = 0;
	int r =0;
 	for( int i = 0 ; i < n; i++ ) {   
      	if (arr[i]<= head)
      		l++;
      	else
      		r++;
      	
   	}
   	int left[l];
   	int right[r];
 	
	
   	for( int i = 0 ; i < n; i++ ) {   
      	if (arr[i]<= head)
      		left[j++]= arr[i];
      		
      	else
      		right[k++]= arr[i]; 
      	
   	}

   	int z = l;
   
    while(z >0) {
        	pos = left[z-1];
           	// calculate absolute distance
        	mov = abs(pos - head);
        	mov_count += mov;
        	head = pos;
        	z--;
       	}
   
    if ( l>=1)
		mov_count+= left[0];
	
   	if ( r >=1)
		mov_count+= right[0];
	

		head = right[0];
		for (int m = 1; m < r; m++) {
        	pos = right[m];
        	// calculate absolute distance
        	mov = abs(pos - head);
        	mov_count += mov;
        	head = pos;
    	}

	return mov_count;
}
//c-scan scheduling

int cscan(int arr[], int head, int n, int disk_size){
	int mov_count = 0;
	int j=0;
	int k=0;
	int pos, mov;
	
	qsort(arr, n, sizeof(int), comparation);
	
	int l = 0;
	int r =0;
 	for( int i = 0 ; i < n; i++ ) {   
      	if (arr[i]<= head)
      		l++;
      	else
      		r++;
      	
   	}
   	int left[l];
   	int right[r];
 	
	
   	for( int i = 0 ; i < n; i++ ) {   
      	if (arr[i]<= head)
      		left[j++]= arr[i];
      	else
      		right[k++]= arr[i];  
   	}
   	
   	for (int m = 0; m < r; m++) {
        	pos = right[m];
        	// calculate absolute distance
        	mov = abs(pos - head);
        	mov_count += mov;
        	head = pos;
    	}
    if ( r >=1)
   		mov_count+= (disk_size -1 - right[r-1]); 
   	mov_count+= disk_size -1 -0;
    if ( l >=1)
   		mov_count+= left[0];
		
   	
   	head = left[0];
   	
   	for (int m = 1; m < l; m++) {
        	pos = left[m];
        	// calculate absolute distance
        	mov = abs(pos - head);
        	mov_count += mov;
        	head = pos;
       	
    	}
	
	
	return mov_count;
}
//look scheduling
int look(int arr[], int head, int n){
	int mov_count = 0;
	int j=0;
	int k=0;
	int pos, mov;
	
	qsort(arr, n, sizeof(int), comparation);
	
	int l = 0;
	int r =0;
 	for( int i = 0 ; i < n; i++ ) {   
      	if (arr[i]<= head)
      		l++;
      	else
      		r++;
      	
   	}
   	int left[l];
   	int right[r];
 	
	
   	for( int i = 0 ; i < n; i++ ) {   
      	if (arr[i]<= head)
      		left[j++]= arr[i];
      	else
      		right[k++]= arr[i];  
   	}
   	
   	for (int m = 0; m < r; m++) {
        	pos = right[m];
        	// calculate absolute distance
        	mov = abs(pos - head);
        	mov_count += mov;
        	head = pos;
    	}
    	
    	if ( r >=1 && l>=1)
   			mov_count+= right[r-1] - left[l-1];
		
   	
   	head = left[l-1];
   	
   	int z = l-2;
   
    while(z >0) {
   	
        	pos = left[z];
        	// calculate absolute distance
        	mov = abs(pos - head);
        	mov_count += mov;
        	head = pos;
       		z--;
    	}
	
	
	return mov_count;
}
//clook scheduling
int clook(int arr[], int head, int n){
	int mov_count = 0;
	int j=0;
	int k=0;
	int pos, mov;
	
	qsort(arr, n, sizeof(int), comparation);
	
	int l = 0;
	int r =0;
 	for( int i = 0 ; i < n; i++ ) {   
      	if (arr[i]<= head)
      		l++;
      	else
      		r++;
      	
   	}
   	int left[l];
   	int right[r];
 	
	
   	for( int i = 0 ; i < n; i++ ) {   
      	if (arr[i]<= head)
      		left[j++]= arr[i];
      	else
      		right[k++]= arr[i];  
   	}
   	
   	for (int m = 0; m < r; m++) {
        	pos = right[m];
        	// calculate absolute distance
        	mov = abs(pos - head);
        	mov_count += mov;
        	head = pos;
    	}
    if ( r >=1 && l>=1)
   		mov_count+= right[r-1] - left[0];
		
   	
   	head = left[0];
   	
   	for (int m = 1; m < l; m++) {
        	pos = left[m];
        	// calculate absolute distance
        	mov = abs(pos - head);
        	mov_count += mov;
        	head = pos;
       	
    	}
	
	
	return mov_count;
}


int main(int argc, char *argv[])
{
	int n = 1000;
	int arr[n];
	int track_valid[n];
	int disk_size = 5000;
	
	long int arg = strtol(argv[1], NULL, 10); 
	int h = (int)arg;
	
	printf("The initial position of the disk head is: %d\n",h); 
	
    for (int i = 0; i < n; i++)  
    {  
        
        arr[i]= rand() % 4999; // use rand() function to get the random number between 0 and 4999 
        track_valid[n] = 0;
        
    }  
    
   printf("The sequence is:\n"); 
    
    for (int i = 0; i < n; i++)  
    {  
        printf("%d ", arr[i]);
        
    }  
    
    printf("\n");

   printf("The total amount of head movement required in FCFS is: %d\n", fcfs(arr, h, n));
   printf("The total amount of head movement required in SSTF is: %d\n", sstf(arr, h, n, track_valid));
   printf("The total amount of head movement required in SCAN is: %d\n", scan(arr, h, n));
   printf("The total amount of head movement required in C-SCAN is: %d\n", cscan(arr, h, n, disk_size));
   printf("The total amount of head movement required in Look is: %d\n", look(arr, h, n));
   printf("The total amount of head movement required in C-Look- is: %d\n", clook(arr, h, n));
   return 0;
}
