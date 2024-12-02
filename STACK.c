#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    void **Stack_Arr;        /*Array to store stack elements*/
    int Stack_Top;           /*Index of the top element*/
    int Stack_Element_Count; /*Current number of elements in the stack*/
    int Stack_Max_Size;      /*Maximum size of the stack*/
} Stack_T;

typedef enum
{
    NULL_POINTER,
    INVALID_FUNCTION,
    VALID_FUNCTION,
} FUN_RET;

typedef enum
{
    FULL_STACK,
    EMPTY_STACK,
    NOT_FULL_NOT_EMPTY_STACK,
} STACK_STATUS;

Stack_T *Create_Stack(FUN_RET *MY_FUN_RET);
void Destroy_Stack(FUN_RET *MY_FUN_RET, Stack_T *Stack_Obj);
STACK_STATUS My_Status(Stack_T *Stack_Obj, FUN_RET *MY_FUN_RET);
void Push(Stack_T *Stack_Obj, void *Data, FUN_RET *MY_FUN_RET);
void *Pop(Stack_T *Stack_Obj, FUN_RET *MY_FUN_RET);
void *Stack_Top_Display(Stack_T *Stack_Obj, FUN_RET *MY_FUN_RET);
int Element_Count_Display(Stack_T *Stack_Obj, FUN_RET *MY_FUN_RET);

    int main()
    {
        Stack_T *Stack_1 = NULL;
        FUN_RET Ret_1;
        int choice;
        int data;

        // Main loop for user to choose options
        while (1)
        {
            // Menu for the user
            printf("\n------ Stack Operations Menu ------\n");
            printf("1. Create Stack\n");
            printf("2. Push Data onto Stack\n");
            printf("3. Pop Data from Stack\n");
            printf("4. Display Stack Top\n");
            printf("5. Display Element Count\n");
            printf("6. Check Stack Status\n");
            printf("7. Destroy Stack\n");
            printf("8. Exit\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice)
            {
            case 1:
                // Create stack
                Stack_1 = Create_Stack(&Ret_1);
                if (Ret_1 == VALID_FUNCTION)
                    printf("Stack created successfully.\n");
                else
                    printf("Failed to create stack.\n");
                break;

            case 2:
                // Push data onto stack
                if (Stack_1)
                {
                    printf("Enter data to push: ");
                    scanf("%d", &data);
                    Push(Stack_1, &data, &Ret_1);
                    if (Ret_1 == VALID_FUNCTION)
                        printf("Data %d pushed onto the stack.\n", data);
                    else
                        printf("Failed to push data onto the stack.\n");
                }
                else
                {
                    printf("Stack is not created yet!\n");
                }
                break;

            case 3:
                // Pop data from stack
                if (Stack_1)
                {
                    void *poppedData = Pop(Stack_1, &Ret_1);
                    if (Ret_1 == VALID_FUNCTION)
                        printf("Popped data: %d\n", *(int *)poppedData);
                    else
                        printf("Failed to pop data from the stack.\n");
                }
                else
                {
                    printf("Stack is not created yet!\n");
                }
                break;

            case 4:
                // Display stack top element
                if (Stack_1)
                {
                    void *topElement = Stack_Top_Display(Stack_1, &Ret_1);
                    if (Ret_1 == VALID_FUNCTION)
                        printf("Stack Top: %d\n", *(int *)topElement);
                    else
                        printf("Failed to display stack top.\n");
                }
                else
                {
                    printf("Stack is not created yet!\n");
                }
                break;

            case 5:
                // Display element count
                if (Stack_1)
                {
                    int elementCount = Element_Count_Display(Stack_1, &Ret_1);
                    if (Ret_1 == VALID_FUNCTION)
                        printf("Number of elements in the stack: %d\n", elementCount);
                    else
                        printf("Failed to display element count.\n");
                }
                else
                {
                    printf("Stack is not created yet!\n");
                }
                break;

            case 6:
                // Check stack status
                if (Stack_1)
                {
                    STACK_STATUS status = My_Status(Stack_1, &Ret_1);
                    if (Ret_1 == VALID_FUNCTION)
                    {
                        switch (status)
                        {
                        case FULL_STACK:
                            printf("The stack is full.\n");
                            break;
                        case EMPTY_STACK:
                            printf("The stack is empty.\n");
                            break;
                        case NOT_FULL_NOT_EMPTY_STACK:
                            printf("The stack is neither full nor empty.\n");
                            break;
                        }
                    }
                    else
                    {
                        printf("Failed to check stack status.\n");
                    }
                }
                else
                {
                    printf("Stack is not created yet!\n");
                }
                break;

            case 7:
                // Destroy the stack
                if (Stack_1)
                {
                    Destroy_Stack(&Ret_1, Stack_1);
                    if (Ret_1 == VALID_FUNCTION)
                        printf("Stack destroyed successfully.\n");
                    else
                        printf("Failed to destroy the stack.\n");
                }
                else
                {
                    printf("Stack is not created yet!\n");
                }
                break;

            case 8:
                // Exit the program
                printf("Exiting the program...\n");
                exit(0);

            default:
                printf("Invalid choice, please try again.\n");
            }
        }

        return 0;
    }


/**
 * @brief Creates a stack with a specified size.
 *
 * @param
 * - FUN_RET *MY_FUN_RET: A pointer to a variable that will store the result of the function execution (valid, invalid, or NULL pointer).
 *
 * @return
 * - Stack_T *: Returns a pointer to the created stack, or NULL if memory allocation fails.
 */
Stack_T *Create_Stack(FUN_RET *MY_FUN_RET)
{
    *MY_FUN_RET = INVALID_FUNCTION;
    Stack_T *My_Stack = NULL;
    int Size = 0;
    printf("Enter Stack Size :");
    scanf("%i", &Size);
    if (Size <= 0)
    {
        printf("Invalid Size\n");
        *MY_FUN_RET = NULL_POINTER;
        return (My_Stack);
    }
    My_Stack = (Stack_T *)malloc(sizeof(Stack_T));
    if (My_Stack)
    {
        My_Stack->Stack_Arr = (void **)calloc(Size, sizeof(void *));
        if (My_Stack->Stack_Arr)
        {

            My_Stack->Stack_Element_Count = 0;
            My_Stack->Stack_Top = -1;
            My_Stack->Stack_Max_Size = Size;
            *MY_FUN_RET = VALID_FUNCTION;
        }
        else
        {
            free(My_Stack);
            *MY_FUN_RET = NULL_POINTER;
            My_Stack = NULL;
        }
    }
    else
    {
        *MY_FUN_RET = NULL_POINTER;
    }

    return (My_Stack);
}

/**
 * @brief Destroys a stack by freeing the allocated memory.
 *
 * @param
 * - FUN_RET *MY_FUN_RET: A pointer to a variable that will store the result of the function execution.
 * - Stack_T *Stack_Obj: A pointer to the stack that needs to be destroyed.
 *
 * @return
 * - void: No return value. It modifies MY_FUN_RET to indicate the result.
 */
void Destroy_Stack(FUN_RET *MY_FUN_RET, Stack_T *Stack_Obj)
{
    *MY_FUN_RET = INVALID_FUNCTION;
    if (Stack_Obj)
    {
        if (Stack_Obj->Stack_Arr)
        {
            free(Stack_Obj->Stack_Arr);
        }
        free(Stack_Obj);
        *MY_FUN_RET = VALID_FUNCTION;
    }
    else
    {
        *MY_FUN_RET = NULL_POINTER;
    }
}

/**
 * @brief Checks the current status of the stack (full, empty, or not full).
 *
 * @param
 * - Stack_T *Stack_Obj: A pointer to the stack whose status is being checked.
 * - FUN_RET *MY_FUN_RET: A pointer to a variable that will store the result of the function execution.
 *
 * @return
 * - STACK_STATUS: Returns one of the following:
 *   - FULL_STACK: If the stack is full.
 *   - EMPTY_STACK: If the stack is empty.
 *   - NOT_FULL_NOT_EMPTY_STACK: If the stack is neither full nor empty.
 */
STACK_STATUS My_Status(Stack_T *Stack_Obj, FUN_RET *MY_FUN_RET)
{
    STACK_STATUS Status = EMPTY_STACK;
    *MY_FUN_RET = INVALID_FUNCTION;

    if (Stack_Obj)
    {
        if (Stack_Obj->Stack_Element_Count == Stack_Obj->Stack_Max_Size)
        {
            Status = FULL_STACK;
        }
        else if (Stack_Obj->Stack_Element_Count == 0)
        {
            Status = EMPTY_STACK;
        }
        else
        {
            Status = NOT_FULL_NOT_EMPTY_STACK;
        }
        *MY_FUN_RET = VALID_FUNCTION;
    }
    else
    {
        *MY_FUN_RET = NULL_POINTER;
    }

    return (Status);
}

/**
 * @brief Pushes data onto the stack.
 *
 * @param
 * - Stack_T *Stack_Obj: A pointer to the stack on which the data will be pushed.
 * - void *Data: A pointer to the data to be pushed onto the stack.
 * - FUN_RET *MY_FUN_RET: A pointer to a variable that will store the result of the function execution.
 *
 * @return
 * - void: No return value. It modifies MY_FUN_RET to indicate whether the push operation succeeded or failed.
 */
void Push(Stack_T *Stack_Obj, void *Data, FUN_RET *MY_FUN_RET)
{
    *MY_FUN_RET = INVALID_FUNCTION;
    if (Stack_Obj && Data)
    {
        STACK_STATUS Status = My_Status(Stack_Obj, MY_FUN_RET);
        if (Status == FULL_STACK)
        {
            printf("\"Stack is full ..... cant push data\"\n");
        }
        else
        {
            Stack_Obj->Stack_Element_Count++;
            Stack_Obj->Stack_Top++;
            Stack_Obj->Stack_Arr[Stack_Obj->Stack_Top] = Data;
            *MY_FUN_RET = VALID_FUNCTION;
        }
    }
    else
    {
        *MY_FUN_RET = NULL_POINTER;
    }
}

/**
 * @brief Pops data from the stack.
 *
 * @param
 * - Stack_T *Stack_Obj: A pointer to the stack from which the data will be popped.
 * - FUN_RET *MY_FUN_RET: A pointer to a variable that will store the result of the function execution.
 *
 * @return
 * - void *: Returns a pointer to the popped data, or NULL if the stack is empty.
 */
void *Pop(Stack_T *Stack_Obj, FUN_RET *MY_FUN_RET)
{
    *MY_FUN_RET = INVALID_FUNCTION;
    void *Temp = NULL;
    if (Stack_Obj)
    {
        STACK_STATUS Status = My_Status(Stack_Obj, MY_FUN_RET);
        if (Status == EMPTY_STACK)
        {
            printf("\"Stack is empty ..... cant pop data\"\n");
        }
        else
        {
            Temp = Stack_Obj->Stack_Arr[Stack_Obj->Stack_Top];
            Stack_Obj->Stack_Element_Count--;
            Stack_Obj->Stack_Top--;
            *MY_FUN_RET = VALID_FUNCTION;
        }
    }
    else
    {
        *MY_FUN_RET = NULL_POINTER;
    }
    return (Temp);
}

/**
 * @brief Displays the top element of the stack.
 *
 * @param
 * - Stack_T *Stack_Obj: A pointer to the stack whose top element will be displayed.
 * - FUN_RET *MY_FUN_RET: A pointer to a variable that will store the result of the function execution.
 *
 * @return
 * - void *: Returns a pointer to the top element of the stack, or NULL if the stack is empty.
 */
void *Stack_Top_Display(Stack_T *Stack_Obj, FUN_RET *MY_FUN_RET)
{
    *MY_FUN_RET = INVALID_FUNCTION;
    void *Temp = NULL;
    if (Stack_Obj)
    {
        STACK_STATUS Status = My_Status(Stack_Obj, MY_FUN_RET);
        if (Status == EMPTY_STACK)
        {
            printf("\"Stack is empty ..... cant display stack top\"\n");
        }
        else
        {
            Temp = Stack_Obj->Stack_Arr[Stack_Obj->Stack_Top];
            *MY_FUN_RET = VALID_FUNCTION;
        }
    }
    else
    {
        *MY_FUN_RET = NULL_POINTER;
    }
    return (Temp);
}

/**
 * @brief Displays the current number of elements in the stack.

 * @param
 * - Stack_T *Stack_Obj: A pointer to the stack whose element count will be displayed.
 * - FUN_RET *MY_FUN_RET: A pointer to a variable that will store the result of the function execution.
 *
 * @return
 * - int: Returns the number of elements in the stack (0 if the stack is empty).
 */
int Element_Count_Display(Stack_T *Stack_Obj, FUN_RET *MY_FUN_RET)
{
    *MY_FUN_RET = INVALID_FUNCTION;
    int Element_count = 0;
    if (Stack_Obj)
    {
        STACK_STATUS Status = My_Status(Stack_Obj, MY_FUN_RET);
        if (Status == EMPTY_STACK)
        {
            printf("\"Stack is empty\"\n");
        }
        else
        {
            Element_count = Stack_Obj->Stack_Element_Count;
            *MY_FUN_RET = VALID_FUNCTION;
        }
    }
    else
    {
        *MY_FUN_RET = NULL_POINTER;
    }
    return (Element_count);
}