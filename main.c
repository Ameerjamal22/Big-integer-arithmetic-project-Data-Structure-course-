#include <stdio.h>
#include <stdlib.h>

#define MAX_DIGITS_COUNT 10000

// Name : AMEER JAMAL RABIE , STUDENT ID : 1211226  , SECTION : 3

typedef struct node* INTEGER ;
typedef struct ListNode * ListOfIntegers ;

/*
 double linked list node to store the number digits and apply operations on it .
 test : OK
*/
struct node {

    // attributes to make the manipulation of the number easier .
    int Value ; // the value of each digit is stored in value  .
    char Sign ; // the sign of the number is stored in the head digit .
    int NumOfDigits ; // the number of digits is stored in the head to make the comparison and manipulation process easier .

    // node link components .
    struct node* Next ;
    struct node* Prev ;
};


/*
  Parameter : string representation of the number , the return value is the head  node pointing to the Integer .
  The Integer is constructed in a way which digits are linked from the least to the most significant digit digit to make the operations implementation easier
  test : OK
*/
INTEGER NewInteger( char StringRepresentedInteger [MAX_DIGITS_COUNT] ){

    INTEGER Head = ( struct node* )malloc( sizeof( struct node ) ) ; // dynamic allocation in memory

    if (Head == NULL ){
        printf("Out of memory \n ") ; // checking if the memory is full
    }

    // Initializing the head node attributes .
    Head -> Value = -1 ; // The value of the head node is -1 since the doubly linked list is done as a cycle so the -1 helps in the traversing process .
    Head -> Sign = '+' ; // Sign is initialized as positive assuming that the positive numbers does not have a positive sign in front .
    Head -> NumOfDigits = 0 ; // Initializes the number of digits to be able to increment it when adding digits

    Head -> Next = NULL ;
    Head -> Prev = NULL ;

    int i = 0 ;

    // checking if the sign of the number is negative
    if ( StringRepresentedInteger[0] == '-'  ){

        Head -> Sign = '-' ;
        i = 1 ;

    }

    /*
     The loop traverses the string and creates node then adds them to the Integer the termination condition is when we reach the digit count limit , or
     when we reach the $ char assuming that the string we take as a parameter is have extra $ after the number .
     test : OK
    */
    while ( i < MAX_DIGITS_COUNT  ){

        if ( !( StringRepresentedInteger[i] >= '0' &&  StringRepresentedInteger[i] <= '9' ) ){
            break ;
        }


        INTEGER Digit = ( struct node * )malloc( sizeof(struct node ) ) ; // dynamic allocation  in memory

        // if the digit is the most significant one we link it to the head node because we need cyclic linked list
        if ( Head -> NumOfDigits == 0 ){

            if ( StringRepresentedInteger[i] == '0' && ( StringRepresentedInteger[i+1] >= '0' &&  StringRepresentedInteger[i+1] <= '9' ) ){
                i ++ ;
                continue ;
            }

            Head -> Next = Digit ;
            Head -> Prev = Digit ;

            Digit -> Prev = Head ;
            Digit -> Next = Head ;


        }

        // adding other digits to the list
        else {

            Digit -> Next = Head -> Next ;
            Digit -> Prev = Head ;

            Head -> Next -> Prev = Digit ;
            Head -> Next = Digit ;
        }

        Digit -> Value = StringRepresentedInteger[i] - '0' ; // Converting the char value into int and putting it in the digit value .
        Head -> NumOfDigits ++ ; // Incrementing the number of digit for the number .
        i ++ ; // Incrementing the loop counter .

    }

    return Head ; // Returns the head node of the INTEGER  .

}

/*
    Takes an Big Integer and a integer digit as parameters and adds the digit as the most significant digit of the big Integer .
    Test : OK .
*/
void AddDigitToMost ( INTEGER N , int digit  ){

    INTEGER temp = ( struct node * )malloc( sizeof( struct node ) ) ; // Initializes a temporary Integer node and allocate a position for it in the memory .
    temp -> Value = digit ; // Gives the passed value of the digit to the new node .


    if ( ( N -> NumOfDigits ) >= 1  ){

        // Links the new node .
        temp -> Prev = N -> Prev ;
        temp -> Next = N ;

        // Adjusts the previous node links .
        N -> Prev -> Next = temp ;
        N -> Prev = temp ;

        ( N -> NumOfDigits ) ++ ; // Incrementing the number of digits for the big Integer .

    }

    else {

        temp -> Prev = N ;
        temp -> Next = N ;

        N -> Next = temp ;
        N -> Prev = temp ;

        ( N -> NumOfDigits ) ++ ;

    }

}


/*
    TEST : OK
*/
void AddDigitToLeast ( int digit , INTEGER Head ){

    INTEGER temp = ( struct node * )malloc( sizeof( struct node ) ) ;
    temp -> Value = digit ;

    if ( Head -> NumOfDigits == 0 ){

        Head -> Next = temp ;
        Head -> Prev = temp ;

        temp -> Next = Head ;
        temp -> Prev = Head ;


    }

    else {

        temp -> Prev = Head ;
        temp -> Next = Head -> Next ;

        Head -> Next -> Prev = temp ;
        Head -> Next = temp ;


    }

    ( Head -> NumOfDigits ) ++ ;

}



/*
    Takes a big Integer as a parameter and cleans all its  extending zeros .
    Test : OK .
*/
void RemoveExtendingZeros ( INTEGER number ){

    INTEGER Pointer = number -> Prev ; // Initializes a pointer that points to the most significant digit that will be used to traverse through the digits .
    INTEGER Temp ; // A temporary Integer pointer that will point to the node we want to delete from the memory .

    // Loops through the big Integers nodes (digits) and deletes all extending zeros until it finds non zero digit  .
    while ( Pointer-> Value == 0 ){

        // Handling the zero number edge case .
        if ( number -> NumOfDigits <= 1 ){
            return ;
        }

        // Removes the links between the last digit and the head node then links the head node to the previous digit
        Pointer -> Prev -> Next = number ;
        number -> Prev = Pointer -> Prev ;
        Temp = Pointer ; // Assigning the node (digit) we want to delete to a temporary pointer to keep track of it .
        Pointer = Pointer -> Prev ;

        free(Temp) ; // Deletes the node (digit) that contains the extending zero from the memory .

        (number -> NumOfDigits ) -- ; // Decrements the number of big integer digits .
    }

    return ;

}

/*
  A void function that prints the Integer .
  test : OK
*/
void PrintInteger ( INTEGER number  ){

    INTEGER temp = number ; // Creating a temporary node to traverse through the number  .


    // Checks if the sign and prints it if so . Assuming that there is no need to print the positive sign .
    if (number -> Sign == '-'){
        printf("-") ;
    }

    temp = temp -> Prev ; // Pointing the temp into the end of the list so it can print the number from most to least significant digit .

    // loops through the digits until it finds the Head node which have -1 Value
    while (temp ->  Value != -1 ){

        printf( "%d" ,temp -> Value ) ;
        temp = temp -> Prev ;

    }
    printf("\n") ;


}

void PrintIntegerToFile ( INTEGER number , FILE *file  ){


    INTEGER temp = number ; // Creating a temporary node to traverse through the number  .

    fprintf(file , "( " ) ;
    // Checks if the sign and prints it if so . Assuming that there is no need to print the positive sign .
    if (number -> Sign == '-'){
        fprintf( file , "-") ;
    }

    temp = temp -> Prev ; // Pointing the temp into the end of the list so it can print the number from most to least significant digit .

    // loops through the digits until it finds the Head node which have -1 Value
    while (temp ->  Value != -1 ){

        fprintf( file , "%d" ,temp -> Value ) ;
        temp = temp -> Prev ;

    }

    fprintf( file , " )");


}




/*
   This code implements a function named ClearINTEGER, which clears a doubly linked list of INTEGER nodes.

   Parameters:
   - Head: The head node of the INTEGER list to be cleared.

   Algorithm:
   1. Store the previous node of the head in a temporary variable 'temp'.
   2. Set the previous node of the head to NULL, effectively breaking the link to the previous node.
   3. Iterate through the list as long as the value of 'temp' is not equal to -1.
      3.1. Update 'temp' to the previous node.
      3.2. Free the memory allocated for the next node of 'temp'.
      3.3. Decrement the 'NumOfDigits' counter in the head node.
   4. Set the next node of the head to NULL, effectively breaking the link to the next node.


*/

void ClearINTEGER(INTEGER Head) {

    INTEGER temp = Head->Prev; // Store the previous node of the head in a temporary variable 'temp'.
    Head->Prev = NULL; // Set the previous node of the head to NULL.

    while (temp->Value != -1) { // Iterate through the list as long as the value of 'temp' is not equal to -1.

        temp = temp->Prev; // Update 'temp' to the previous node.
        free(temp->Next); // Free the memory allocated for the next node of 'temp'.
        (Head->NumOfDigits)--; // Decrement the 'NumOfDigits' counter in the head node.

    }

    Head->Next = NULL; // Set the next node of the head to NULL.

}


/*
   This code implements a function named DisposeInteger, which disposes of an INTEGER node.

   Parameters:
   - N: The INTEGER node to be disposed.

   Algorithm:
   1. Call the 'ClearINTEGER' function to clear the doubly linked list associated with the INTEGER node.
   2. Free the memory allocated for the INTEGER node itself.

*/

void DisposeInteger(INTEGER N) {

    ClearINTEGER(N); // Call the 'ClearINTEGER' function to clear the doubly linked list associated with the INTEGER node.
    free(N); // Free the memory allocated for the INTEGER node itself.

}



/*
   This code implements a function named ConvertIntToINTEGER, which converts an integer into an INTEGER node.

   Parameters:
   - N: The integer to be converted.

   Return:
   - Result: An INTEGER node representing the converted integer.

   Algorithm:
   1. Allocate memory for the INTEGER node using 'malloc'.
   2. Set the 'Sign' member of the INTEGER node to '+'.
   3. Initialize the 'NumOfDigits' member of the INTEGER node to 0.
   4. Set the initial 'Value' of the INTEGER node to -1.
   5. If the input integer N is 0, add a digit '0' to the most significant position of the INTEGER node.
   6. While N is greater than 0:
      6.1. Add the last digit of N (N % 10) to the most significant position of the INTEGER node.
      6.2. Divide N by 10 to remove the last digit.
   7. Return the converted INTEGER node.

*/
INTEGER ConvertIntToINTEGER(int N) {

    INTEGER Result = (struct node *)malloc(sizeof(struct node)); // Allocate memory for the INTEGER node using 'malloc'.
    Result->Sign = '+'; // Set the 'Sign' member of the INTEGER node to '+'.
    Result->NumOfDigits = 0; // Initialize the 'NumOfDigits' member of the INTEGER node to 0.
    Result->Value = -1; // Set the initial 'Value' of the INTEGER node to -1.

    if (N == 0) {

        AddDigitToMost(Result, 0); // Add a digit '0' to the most significant position of the INTEGER node.

    }

    while (N > 0) {

        AddDigitToMost(Result, (N % 10)); // Add the last digit of N (N % 10) to the most significant position of the INTEGER node.
        N /= 10; // Divide N by 10 to remove the last digit.

    }

    return Result; // Return the converted INTEGER node.

}


/*
    Parameters : two Integer One , Two - Return value : 1 (if one absolute value is bigger ) , -1 (if Two absolute value is bigger) , 0 (if they are equal) .
    the function first compares the size of them if one of them have more digits then for sure it bigger , otherwise it compares both of them
    digit by digit from most to least significant digit  .
    Test : OK
*/
int CompareIntegersAbs( INTEGER One , INTEGER Two ){

    int result = 0 ; // Initializes the return value to zero which means they are equal .

    //  Checks if one them have more digits than the other and returns a values based of this comparison .
    if ( (One -> NumOfDigits) > (Two -> NumOfDigits) ){

        return 1 ;

    }

    else if ( (One -> NumOfDigits ) < (Two ->NumOfDigits) ){

        return -1 ;

    }

    // In this case both of Integers have the same number of digits so the comparison is done between digits from most to least significant digit .
    else {

        INTEGER First = One -> Prev ; // Initializes a pointer to the node that contains the most significant digit in the first number .
        INTEGER Second = Two -> Prev ;// Initializes a pointer to the node that contains the most significant digit in the second number .

        // Loops through the digits until a difference is found or the head is reached .
        while ( First -> Value != -1 ){

            //Checks if the current digit of each number is different and updating the result value based on the comparis

            if( Second -> Value > First -> Value ){

                result = -1 ;
                break ;

            }

            else if ( First -> Value > Second -> Value ){

                result = 1 ;
                break ;

            }

            First = First -> Prev ; // Updating the value of the pointer to the previous digit of the first number .
            Second = Second -> Prev ; // Updating the value of the pointer to the previous digit of the second number .

        }

    }

    return result ; // returns the result of the comparison between
}


/*
    Takes two big integers as a parameter and returns the result of their absolute value addition .
    Test : OK
*/
INTEGER AddIntegersMagnitude( INTEGER One , INTEGER Two ){

    INTEGER First , Second ; // Defines two pointer that will help with the addition operation

    // Compares between the passed big integers and based of the comparison gives value to the pointers defined above .

    if ( CompareIntegersAbs( One , Two ) >= 0  ){

        First = One -> Next ;
        Second = Two -> Next ;

    }

    else {

        First = Two -> Next ;
        Second = One -> Next ;

    }



    int Size = ( First -> Prev -> NumOfDigits ) + 1 ; // Initializes the size variable .

    int AdditionTempArray[Size] ;
    for (int i = 0 ; i < Size ; i ++ )AdditionTempArray[i] = 0 ; // Initializes the temp array values to zero since values will be added to it

    int Carry = 0 ; // initializes the carry variable that will help in the addition operation .
    int TempSum = 0 ;

    int i = 0 ;

    /*
        traverses through the big integer nodes (digits) and adds each pair of them from the least to the most significant one and keeping track of the carry
        until we reach the bigger number last digit
    */
    while ( First -> Value != -1 ){

        TempSum = 0 ;

        if( Second -> Value == -1 ){

            TempSum = ( First -> Value ) + Carry ;
            AdditionTempArray[i] = TempSum % 10 ;
            Carry = TempSum / 10 ;

            First = First -> Next ;

        }

        else {

            TempSum = ( First -> Value ) + ( Second -> Value ) + Carry ;
            AdditionTempArray[i] = TempSum % 10 ;
            Carry = TempSum /10 ;

            First = First -> Next ;
            Second = Second -> Next ;

        }

        i ++ ;
    }
    AdditionTempArray[Size -1 ] += Carry ;

    // converting the integer array into string and passing it to the INTEGER creator to create new integer .
    char AnswerString[MAX_DIGITS_COUNT] ;
    for( i = 0 ; i < MAX_DIGITS_COUNT ; i ++ )AnswerString[i] = '$' ;

    for( i = 0 ; i < Size ; i ++ )AnswerString[i] = AdditionTempArray[ Size - i - 1 ] + '0' ;


    INTEGER Result = NewInteger( AnswerString ) ;

    return Result ; // returns the result of the addition .

}


/*
    Parameters : two bit integers one , two / return value : the difference between them represented in big integer .
    Compares the two integers and subtract the smaller one from the smaller .
    Test : OK
*/
INTEGER FindDiff ( INTEGER One , INTEGER Two ){

    INTEGER First , Second ; // Defines the pointers that will be used when traversing .

    // the comparison and pointer assignment that help to implement the find difference algorithm .

    if ( CompareIntegersAbs( One , Two ) >= 0 ){

        First = One -> Next ;
        Second = Two -> Next  ;

    }

    else {

        First = Two -> Next ;
        Second = One -> Next ;

    }

    // defines the head of the big integer and initializes its attributes .
    INTEGER ResultHead = ( struct node * )malloc( sizeof( struct node ) ) ;
    ResultHead -> NumOfDigits = 0 ;
    ResultHead -> Value = -1 ;
    ResultHead -> Sign = '+' ;

    // initializes the borrow and temp sum to use them in the subtraction
    int borrow = 0 ;
    int TempSum = 0 ;

    /*
        traverses through the nodes (digits) of the big integer and keeps track of the borrow
    */
    while ( ( First -> Value ) != -1 ){

        TempSum = 0 ; // initializes the temp sum for every loop to work on it .

        // handling the case where both of the big integers have a digits
        if ( Second -> Value != -1 ){

            TempSum = ( First -> Value ) - ( ( Second -> Value ) + borrow ) ; // the value of the subtraction

            // if the value of the subtraction between the digits and borrow is less than zero the program borrow from the next digit
            if ( TempSum < 0 ){

                TempSum += 10 ;
                borrow = 1 ;

            }
            // if the value is not negative then the the borrow value is updated to zero .
            else {

                borrow = 0 ;

            }


            Second = Second -> Next ; // updating the value of the second big integer pointer .

        }

        // handling the case where the digits of the second number are finished
        else {

            TempSum = ( First -> Value ) - borrow ;  // the value of the subtraction between the first big integer digit and the borrow

            // if the value of the subtraction between the digits and borrow is less than zero the program borrow from the next digit
            if ( TempSum < 0 ){

                TempSum += 10 ;
                borrow = 1 ;

            }

            // if the value is not negative then the the borrow value is updated to zero .
            else {

                borrow = 0 ;

            }


        }


        AddDigitToMost( ResultHead , TempSum ) ; // appending the new digit to the big integer  .

        First = First -> Next ; // updating the pointer of the first number digits .

    }

    RemoveExtendingZeros( ResultHead ) ; // removing the extending zeros from the result big integer

    return ResultHead ; // returning the result big integer .

}



/*
   This code implements a function named AddIntegers, which adds two INTEGER nodes.

   Parameters:
   - One: The first INTEGER node to be added.
   - Two: The second INTEGER node to be added.

   Return:
   - Result: An INTEGER node representing the sum of the two input INTEGER nodes.



   Algorithm:
   1. Declare a variable 'Result' of type INTEGER to store the result of the addition.
   2. If both 'One' and 'Two' have a positive sign ('+'), add their magnitudes using the 'AddIntegersMagnitude' function.
   3. If 'One' and 'Two' have different signs:
      3.1. Declare a variable 'PositiveNum' of type INTEGER to store the positive INTEGER node.
      3.2. If 'One' has a positive sign, assign 'One' to 'PositiveNum'; otherwise, assign 'Two' to 'PositiveNum'.
      3.3. Find the difference between 'One' and 'Two' using the 'FindDiff' function and assign it to 'Result'.
      3.4. Check if the absolute value of 'One' is greater than the absolute value of 'Two' and if 'PositiveNum' is not equal to 'One'.
         3.4.1. If the condition is true, set the sign of 'Result' to '-'.
      3.5. Check if the absolute value of 'Two' is greater than the absolute value of 'One' and if 'Two' has a negative sign ('-').
         3.5.1. If the condition is true, set the sign of 'Result' to '-'.
   4. If both 'One' and 'Two' have the same sign ('-'), add their magnitudes using the 'AddIntegersMagnitude' function.
      4.1. Set the sign of 'Result' to '-'.

*/

INTEGER AddIntegers(INTEGER One, INTEGER Two) {

    INTEGER Result;

    if ((One -> Sign == '+') && (Two -> Sign == '+')) {

        Result = AddIntegersMagnitude(One, Two); // Add the magnitudes of 'One' and 'Two'.

    }
    else if ((One->Sign != Two->Sign)) {
        INTEGER PositiveNum;

        if (One->Sign == '+') {
            PositiveNum = One;
        }
        else {
            PositiveNum = Two;
        }

        Result = FindDiff(One, Two); // Find the difference between 'One' and 'Two'.

        if ((CompareIntegersAbs(One, Two) == 1) && (PositiveNum != One)) {
            Result->Sign = '-'; // Set the sign of 'Result' to '-' if the absolute value of 'One' is greater than 'Two'.
        }
        else if ((CompareIntegersAbs(Two, One) == 1) && (Two->Sign == '-')) {
            Result->Sign = '-'; // Set the sign of 'Result' to '-' if the absolute value of 'Two' is greater than 'One' and 'Two' has a negative sign.
        }
    }
    else {
        Result = AddIntegersMagnitude(One, Two); // Add the magnitudes of 'One' and 'Two'.
        Result->Sign = '-'; // Set the sign of 'Result' to '-'.
    }

    return Result; // Return the result of the addition.
}



/*
   This code defines a function named SubtractIntegers that subtracts two integers represented by the parameters One and Two of type INTEGER.

   Parameters:
   - One: An INTEGER representing the first integer.
   - Two: An INTEGER representing the second integer.

   Returns:
   - Result: An INTEGER representing the result of subtracting Two from One.

*/

INTEGER SubtractIntegers(INTEGER One, INTEGER Two) {
    INTEGER Result;

    if (One -> Sign == '+' && Two -> Sign == '+') {

        // Subtract Two from One when both have positive sign.
        Result = FindDiff(One, Two);

        if (CompareIntegersAbs(Two, One) == 1) {

            // If Two is greater than One in absolute value, change the sign of the result to negative.
            Result -> Sign = '-';

        }

    } else if (One -> Sign != Two -> Sign) {

        // Add the magnitudes of One and Two when they have different signs.
        Result = AddIntegersMagnitude(One, Two);

        if (One -> Sign == '-') {

            // If One is negative, the result will be negative.
            Result->Sign = '-';

        }
    } else {

        // Subtract Two from One when both have the same sign.
        Result = FindDiff(One, Two);

        if (CompareIntegersAbs(One, Two) == 1) {

            // If One is greater than Two in absolute value, change the sign of the result to negative.
            Result -> Sign = '-';

        }
    }

    return Result;
}


/*
    takes two INTEGERS and multiplies them and returns the result as INTEGER
    Test : OK
*/
INTEGER Multiply ( INTEGER One , INTEGER Two ){

    // Initializing the variables required for the multiplication algorithm .
    int Size = One -> NumOfDigits + Two -> NumOfDigits ; // Size for the array that will store the answer digits multiplication is done cant exceed there total number of digits


    int AnswerTempDigits[Size] ; // Creates the array that will store the digits when the multiplication is done .
    for( int i = 0 ; i < Size ; i ++ ) AnswerTempDigits[i] = 0 ; // Initializing the array elements with zero since values will be added to them .

    // Creates two pointers that will point to the least significant digit of each number to traverse them while the multiplication is executed .
    INTEGER multiplicand = One -> Next  ;
    INTEGER multiplier = Two -> Next ;

    // Initialize two pointers to determine the index of the array element that the result of two digits multiplication is added to .
    int point1 = 0 ; // Initialize the first pointer that will be the position that we start add values from (shifted after we multiply a digit of the multiplier with all the digits of the multiplicand ) .
    int point2 ; // Defining the second pointer

    /*
        In this loop each digit of the multiplier is multiplied by all the digits of the multiplicand and then the pointer that
        indicate the position to start adding from is incremented until we finish multiplying all the multiplier digits .
    */
    while ( multiplier ->  Value  != -1 ){

        point2 = point1 ;

        while ( multiplicand -> Value  != -1 ){

            AnswerTempDigits[point2] += ( multiplier -> Value ) * ( multiplicand -> Value ) ;
            point2 ++ ;
            multiplicand = multiplicand -> Next ;

        }

        point1 ++ ;
        multiplicand = One -> Next ;
        multiplier = multiplier -> Next ;

    }


    int carry = 0 ; // Initializes the carry variable that will help to adjust the digit values in the array to the right values .

    // Loops through the digits of the array and updates its values by using mod 10 then takes the left digits to the next digit by dividing the value by 10 until the end .
    for (int k = 0 ; k < Size ; k ++ ){

        AnswerTempDigits[k] += carry ; // Adds the carry from previous digit to the current digit

        carry = AnswerTempDigits[k] / 10 ; // Updates the carry value by dividing the current digit value by 10
        AnswerTempDigits[k] %= 10 ; // Determines the final value of each digit in the result .

    }

    char AnswerString[MAX_DIGITS_COUNT] ; // Defines the answer String that will be passed to NewInteger function to create the result INTEGER .

    for( int k = 0 ; k < MAX_DIGITS_COUNT ; k ++ ) AnswerString[k] = '$' ; // Initializes its characters with $ to make it fit for conversion

    // Stores the digits of the result in the String of the result starting from most to least significant digit .
    for( int k = 0 ; k < Size ; k ++ ){

        AnswerString[k] = AnswerTempDigits[ Size - 1 - k ] + '0' ;

    }

    // Passes the Result string to new Integer function and handling the sign of the result

    INTEGER Result = NewInteger( AnswerString ) ;

    if ( One -> Sign != Two -> Sign ){
        Result -> Sign = '-' ;
    }

    return Result ; // Returns the Result of the multiplication  .

}



/*
   This code implements a function named BinarySearchDiv, which performs binary search to find the largest integer quotient (within the range of 0 to 9) when dividing two INTEGER nodes.

   Parameters:
   - temp: The dividend INTEGER node.
   - Divider: The divisor INTEGER node.

   Return:
   - Ans: An INTEGER node representing the largest integer quotient.

   Algorithm:
   1. Initialize variables: L = 0 (left boundary), R = 9 (right boundary), and Ans = ConvertIntToINTEGER(0) (initial answer).
   2. Declare a variable 'mid' to store the middle value.
   3. Perform binary search until the left boundary (L) is less than or equal to the right boundary (R).
      3.1. Calculate the middle value using mid = L + (R - L) / 2.
      3.2. Compare the absolute value of the product of the current middle value and Divider with the absolute value of temp using CompareIntegersAbs.
         3.2.1. If the comparison result is less than or equal to 0, update Ans with the current middle value and move the left boundary (L) to mid + 1.
         3.2.2. Otherwise, move the right boundary (R) to mid - 1.
   4. Return Ans, which represents the largest integer quotient.

*/

INTEGER BinarySearchDiv(INTEGER temp, INTEGER Divider) {

    int L = 0, R = 9; // Initialize left and right boundaries.
    INTEGER Ans = ConvertIntToINTEGER(0); // Initialize the answer as 0.

    int mid;

    while (L <= R) { // Perform binary search until L <= R.

        mid = L + (R - L) / 2; // Calculate the middle value.

        if (CompareIntegersAbs(Multiply(ConvertIntToINTEGER(mid), Divider), temp) <= 0) {

            // If the absolute value of the product of mid and Divider is less than or equal to the absolute value of temp.
            Ans = ConvertIntToINTEGER(mid); // Update Ans with the current middle value.
            L = mid + 1; // Move the left boundary to mid + 1.

        }

        else {

            R = mid - 1; // Move the right boundary to mid - 1.
        }
    }

    return Ans; // Return the largest integer quotient.
}



/*
   This code implements a function named IntegersDivision, which performs division of two INTEGER nodes and calculates the quotient and remainder.

   Parameters:
   - Dividend: The dividend INTEGER node.
   - Divider: The divisor INTEGER node.
   - Remainder: A pointer to an INTEGER node to store the remainder.

   Return:
   - Result: An INTEGER node representing the quotient.


   Algorithm:
   1. Allocate memory for the Result INTEGER node using 'malloc'.
   2. Set the 'Sign', 'NumOfDigits', and 'Value' members of the Result INTEGER node.
   3. Initialize a temp INTEGER node with the value of Dividend's previous node.
   4. Initialize a pointer to track the current position in Dividend.
   5. If the absolute value of the largest integer quotient (found using BinarySearchDiv) is less than 1:
      5.1. Set the Remainder to Dividend and return 0 as the Result.
   6. Perform the division algorithm:
      6.1. While the absolute value of the largest integer quotient of temp and Divider is less than 1:
         6.1.1. Add the least significant digit of the current pointer value to temp.
         6.1.2. Move the pointer to the previous node.
      6.2. Initialize Key and Temp2 variables.
      6.3. While true:
         6.3.1. Set Key to the largest integer quotient of temp and Divider using BinarySearchDiv.
         6.3.2. If the absolute value of Key is less than 1:
            6.3.2.1. Add the least significant digit of the current pointer value to temp.
            6.3.2.2. Add 0 to the least significant position of Result.
         6.3.3. Else:
            6.3.3.1. Add the next digit of Key to the least significant position of Result.
            6.3.3.2. Set Temp2 to temp.
            6.3.3.3. Calculate the new temp by finding the difference between Temp2 and the product of Key and Divider.
            6.3.3.4. Add the least significant digit of the current pointer value to temp.
            6.3.3.5. Dispose of the Temp2 INTEGER node.
         6.3.4. If the value of the current pointer is -1, set Remainder to temp and break the loop.
         6.3.5. Move the pointer to the previous node.
   7. If the signs of Dividend and Divider are not the same, set the sign of Result to '-'.
   8. Return Result, representing the quotient.

*/

INTEGER IntegersDivision(INTEGER Dividend, INTEGER Divider, INTEGER *Remainder) {

    INTEGER Result = (struct node *)malloc(sizeof(struct node)); // Allocate memory for the Result INTEGER node.

    Result->Sign = '+'; // Set the sign of Result to '+'.
    Result->NumOfDigits = 0; // Initialize the number of digits of Result to 0.
    Result->Value = -1; // Set the value of Result to -1.

    INTEGER temp = ConvertIntToINTEGER(Dividend->Prev->Value); // Initialize temp with the value of Dividend's previous node.

    INTEGER pointer = Dividend->Prev->Prev; // Initialize a pointer to track the current position in Dividend.

    if (CompareIntegersAbs(BinarySearchDiv(Dividend, Divider), ConvertIntToINTEGER(1)) == -1) {

        // If the absolute value of the largest integer quotient is less than 1.
        *Remainder = Dividend; // Set Remainder to Dividend.
        return ConvertIntToINTEGER(0); // Return 0 as the Result.

    }

    while (CompareIntegersAbs(BinarySearchDiv(temp, Divider), ConvertIntToINTEGER(1)) == -1) {

        // While the absolute value of the largest integer quotient of temp and Divider is less than 1.
        AddDigitToLeast((pointer->Value), temp); // Add the least significant digit of the current pointer value to temp.
        pointer = pointer->Prev; // Move the pointer to the previous node.

    }

    INTEGER Key, Temp2;

    while (1) {
        // Perform the division algorithm.
        Key = BinarySearchDiv(temp, Divider); // Find the largest integer quotient using BinarySearchDiv.

        if (CompareIntegersAbs(Key, ConvertIntToINTEGER(1)) == -1) {

            // If the absolute value of Key is less than 1.
            AddDigitToLeast((pointer->Value), temp); // Add the least significant digit of the current pointer value to temp.
            AddDigitToLeast(0, Result); // Add 0 to the least significant position of Result.

        }
        else {

            // If the absolute value of Key is greater than or equal to 1.
            AddDigitToLeast(Key->Next->Value, Result); // Add the next digit of Key to the least significant position of Result.
            Temp2 = temp; // Store the value of temp in Temp2.
            temp = FindDiff(Temp2, Multiply(Key, Divider)); // Calculate the new temp by finding the difference between Temp2 and the product of Key and Divider.
            AddDigitToLeast(pointer->Value, temp); // Add the least significant digit of the current pointer value to temp.
            DisposeInteger(Temp2); // Free the memory occupied by Temp2.

        }

        if (pointer->Value == -1) {

            // If the value of the current pointer is -1.
            *Remainder = temp ; // Set Remainder to temp.
            break ; // Break the loop.

        }

        pointer = pointer -> Prev ; // Move the pointer to the previous node.
    }

    if (Dividend -> Sign != Divider -> Sign ) {

        // If the signs of Dividend and Divider are not the same.
        Result->Sign = '-'; // Set the sign of Result to '-'.

    }

    return Result; // Return Result, representing the quotient.
}



/*
   This code defines a structure named ListNode, which represents a node in a linked list.

   Members:
   - INT: A pointer to a structure of type node. The type and purpose of node are assumed to be defined elsewhere.
   - Next: A pointer to the next ListNode in the linked list.
   - Last: A pointer to the previous ListNode in the linked list.
   - index: An integer representing the index or position of the current ListNode in the linked list.
   - count: An integer representing the count or number of elements in the ListNode or the linked list.
.
*/

struct ListNode {

    struct node *INT; // A pointer to a structure of type node.
    struct ListNode *Next; // A pointer to the next ListNode in the linked list.
    struct ListNode *Last; // A pointer to the previous ListNode in the linked list.

    int index; // An integer representing the index or position of the current ListNode.
    int count; // An integer representing the count or number of elements in the ListNode or the linked list.

};



/*
   This code defines a function named ReadInputFile that reads integers from a file and stores them in a linked list.

   Returns:
   - Ints: A pointer to the head of the linked list (ListOfIntegers) containing the read integers.

*/

ListOfIntegers ReadInputFile() {

    ListOfIntegers Ints = (struct ListNode *)malloc(sizeof(struct ListNode));
    Ints->Last = Ints;
    Ints->index = 0;
    Ints->count = 0;
    Ints->Next = NULL;

    char filename[100];
    FILE *file;
    char InputInteger[MAX_DIGITS_COUNT];

    // Get the filename from the user
    printf("Enter the filename: ");
    scanf("%s", filename);

    // Open the file in read mode
    file = fopen(filename, "r");

    if (file == NULL) {

        printf("Failed to open the file.\n");
        return Ints;

    }

    for (int i = 0; i < MAX_DIGITS_COUNT; i++) {

        InputInteger[i] = '$';

    }

    INTEGER Current;
    struct ListNode *temp;

    while (fgets(InputInteger, MAX_DIGITS_COUNT, file) != NULL) {
        Current = NewInteger(InputInteger);
        temp = (struct ListNode *)malloc(sizeof(struct ListNode));

        (Ints->count)++;
        temp -> index = Ints -> count;
        temp -> INT = Current;

        Ints -> Last -> Next = temp;
        temp -> Next = NULL;
        Ints -> Last = temp;

        for (int i = 0; i < MAX_DIGITS_COUNT; i++) {

            InputInteger[i] = '$';

        }
    }

    fclose(file);

    return Ints;
}



/*
   This code defines a function named DisplayListOfIntegers that prints the integers stored in a linked list along with their corresponding indices.

   Parameters:
   - List: A pointer to the head of the linked list (ListOfIntegers) containing the integers to be displayed.

*/

void DisplayListOfIntegers(ListOfIntegers List) {
    ListOfIntegers temp = List->Next;

    while (1) {

        printf("%d : ", temp->index);

        PrintInteger(temp->INT);

        if (temp->Next == NULL) {
            break;
        }

        temp = temp->Next;
    }

    return;
}



/*
   This code defines a function named GetIntegerByIndex that retrieves an INTEGER object from a linked list based on its corresponding index.

   Parameters:
   - L: A pointer to the head of the linked list (ListOfIntegers) containing the integers.
   - Index: The index of the INTEGER object to retrieve.

   Returns:
   - The INTEGER object associated with the specified index.

*/
INTEGER GetIntegerByIndex(ListOfIntegers L, int Index) {

    ListOfIntegers temp = L->Next;

    while (temp != NULL) {

        if (temp -> index == Index) {

            break;

        }

        temp = temp -> Next;

    }

    return temp -> INT ;

}



/*
   This code defines a structure named ExpressionNode, representing a node in an expression linked list.

   Members:
   - Opperand1: An INTEGER object representing the first operand of the expression.
   - Opperand2: An INTEGER object representing the second operand of the expression.
   - Operation: A char representing the operation performed on the operands.
   - Result: An INTEGER object representing the result of the expression.
   - Remainder: An INTEGER object representing the remainder of a division operation.
   - Last: A pointer to the previous node in the expression linked list.
   - Next: A pointer to the next node in the expression linked list.

*/
struct ExpressionNode {
    INTEGER Opperand1;
    INTEGER Opperand2;
    char Operation;
    INTEGER Result;
    INTEGER Remainder;

    struct ExpressionNode* Last;
    struct ExpressionNode* Next;
};



/*
   This code defines a function named CreateExpressionsList that creates and initializes an empty expression linked list.

   Returns:
   - A pointer to the head of the created expression linked list.

   Assumptions:
   - The following types and functions are defined and available:
     - struct ExpressionNode: A structure representing a node in the expression linked list.
*/
struct ExpressionNode* CreateExpressionsList() {

    struct ExpressionNode* Head = (struct ExpressionNode*)malloc(sizeof(struct ExpressionNode));

    Head -> Next = NULL;
    Head -> Last = Head;

    return Head;
}



/*
   This code defines a function named AppendExpression that appends a new expression node to the end of the expression linked list.

   Parameters:
   - Operand1: An INTEGER object representing the first operand of the expression.
   - Operand2: An INTEGER object representing the second operand of the expression.
   - operation: A char representing the operation performed on the operands.
   - result: An INTEGER object representing the result of the expression.
   - ListOfExpressions: A pointer to the head of the expression linked list.
   - Rem: An INTEGER object representing the remainder of a division operation.

*/

void AppendExpression(INTEGER Operand1, INTEGER Operand2, char operation, INTEGER result, struct ExpressionNode* ListOfExpressions, INTEGER Rem) {

    struct ExpressionNode* temp = (struct ExpressionNode*)malloc(sizeof(struct ExpressionNode));

    temp->Opperand1 = Operand1;
    temp->Opperand2 = Operand2;
    temp->Operation = operation;
    temp->Result = result;
    temp->Remainder = Rem;

    ListOfExpressions->Last->Next = temp;
    ListOfExpressions->Last = temp;
    temp->Next = NULL;
}




/*
   This code defines a function named PrintResultsToFile that prints the results of expressions stored in the expression linked list to a file.

   Parameters:
   - List: A pointer to the head of the expression linked list.

*/

void PrintResultsToFile(struct ExpressionNode* List) {

    FILE* file;
    char filename[] = "output.txt";

    // Open the file in write mode
    file = fopen(filename, "w");
    if (file == NULL) {

        printf("Failed to open the file.\n");
        return;

    }

    if (List->Next == NULL) {

        printf("There are no results to print yet.\n");
        fclose(file);
        return;

    }

    struct ExpressionNode* temp = List->Next;

    while (temp != NULL) {

        PrintIntegerToFile(temp->Opperand1, file);
        fprintf(file, " %c ", temp->Operation);
        PrintIntegerToFile(temp->Opperand2, file);
        fprintf(file, " = ");
        PrintIntegerToFile(temp->Result, file);

        if (temp->Operation == '/') {
            fprintf(file, "  Remainder = ");
            PrintIntegerToFile(temp->Remainder, file);
        }

        fprintf(file, "\n");

        temp = temp->Next;
    }

    // Close the file
    fclose(file);
}


/*
    This code expresses the menu that will be displayed to the user each time after picking a choice .
*/
void TextMessage (){


    printf("\n\n\nEnter the number of the option to chose it :\n") ;
    printf("1- Read input from file .\n") ;
    printf("2- Display Integers .\n") ;
    printf("3- Add two Integers .\n") ;
    printf("4- Subtract two Integers . \n") ;
    printf("5- Multiply two Integers . \n") ;
    printf("6- Divide two Integers . \n") ;
    printf("7- Print all results to the output file .\n");
    printf("8- Exit. \n\n\n") ;

}


/*
   This code defines a function named DisplayMenu that displays a menu and handles user choices for performing various operations on integers.
*/

void DisplayMenu (){

    printf(" Program starts ") ;

    ListOfIntegers List ;

    struct ExpressionNode * Expressions = CreateExpressionsList() ;

    int choice ;

    while (1){

        TextMessage() ;


        scanf("%d", &choice ) ;

        if ( choice == 1 ){

            List = ReadInputFile() ;

            if (List ->count != 0 ){

                printf("TOOK THE INPUT SUCCESSFULLY ") ;

            }

        }

        else if ( choice == 2  ){

            DisplayListOfIntegers( List ) ;

        }

        else if ( choice == 3 ){

            INTEGER One , Two ;

            int index1 , index2 ;

            printf("Enter the index of the first Integer :") ;
            scanf("%d", &index1 ) ;

            printf("Enter the index of the second Integer :") ;
            scanf("%d", &index2 ) ;

            One = GetIntegerByIndex( List , index1 ) ;
            Two = GetIntegerByIndex( List , index2 ) ;

            AppendExpression( One , Two , '+' , AddIntegers( One , Two ) , Expressions , ConvertIntToINTEGER(0) ) ;

        }

        else if ( choice == 5 ){

            INTEGER One , Two ;

            int index1 , index2 ;

            printf("Enter the index of the first Integer :") ;
            scanf("%d", &index1 ) ;

            printf("Enter the index of the second Integer :") ;
            scanf("%d", &index2 ) ;

            One = GetIntegerByIndex( List , index1 ) ;
            Two = GetIntegerByIndex( List , index2 ) ;

            AppendExpression( One , Two , 'X' , Multiply( One , Two ) , Expressions , ConvertIntToINTEGER(0) ) ;

        }

        else if ( choice == 4 ){

            INTEGER One , Two ;

            int index1 , index2 ;

            printf("Enter the index of the Integer you want to subtract from :") ;
            scanf("%d", &index1 ) ;

            printf("Enter the index of the Integer you want to subtract : ") ;
            scanf("%d", &index2 ) ;

            One = GetIntegerByIndex( List , index1 ) ;
            Two = GetIntegerByIndex( List , index2 ) ;

            AppendExpression( One , Two , '-' , SubtractIntegers( One , Two ) , Expressions , ConvertIntToINTEGER(0) ) ;

        }

        else if ( choice == 6 ){

            INTEGER One , Two ;

            int index1 , index2 ;

            printf("Enter the index of the first Integer :") ;
            scanf("%d", &index1 ) ;

            printf("Enter the index of the second Integer :") ;
            scanf("%d", &index2 ) ;

            One = GetIntegerByIndex( List , index1 ) ;
            Two = GetIntegerByIndex( List , index2 ) ;

            if ( CompareIntegersAbs( Two , ConvertIntToINTEGER(0) ) == 0  ){

                printf("dividing a number by zero is not possible ") ;
                continue ;

            }

            INTEGER REM ;
            INTEGER ANS = IntegersDivision(One , Two ,&REM) ;


            AppendExpression( One , Two , '/' , ANS , Expressions , REM ) ;

        }

        else if ( choice == 7 ){
            PrintResultsToFile( Expressions ) ;
        }

        else if (choice == 8 ){

            break ;

        }

        else {

            printf("Invalid choice . \n") ;

        }



    }

    printf("Thank you for using the program ..... \n") ;

}




int main()
{

    DisplayMenu() ; // calling the function that controls the flow of the program .


    return 0;
}
