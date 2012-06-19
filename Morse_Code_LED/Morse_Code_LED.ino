/*
  By Matthew Herbst - Last updated 6/19/2012
  Morse Code LED - Have an LED display the entered text in Morse Code
  Please feel free to contact me with bugs/suggestions at herbstmb@muohio.edu
 */
 
//Choose the pin that has the LED connected to it
const int led = 7;

//Morse Code Timings
const int MULTIPLIER = 2.5; //Used to slow down the program to make dots/dashes more visble. Change as needed
const double DOT = 92.3 * MULTIPLIER; //1 dot
const double DASH = 276.9 * MULTIPLIER; //3 dots
const double TIMING_SPACE = 92.3 * MULTIPLIER; //1 dot - the space between dots/dashes of a single charachter
const double CHAR_SPACE = 276.9 * MULTIPLIER; //3 dots - the space between individual charachters
const double WORD_SPACE = 646.1; //7 dots - the space between words (when a ' ' is received)

//Morse Code Timings Holder Array Setup
const int NUM_CHARS = 96;
const int MORSE_MAX_CHAR_SIZE = 7;

//Array placement is based on character ASCII value
//IF YOU ADD A NEW VALUE BE SURE TO ADD TO TO THE ACCEPTED CHAR IF CHECK
//Note: since there is no difference between lower/upper case in Morse, only upper is entered here - lower case is converted to upper using ASCII arithmatic
int TIMINGS[NUM_CHARS][MORSE_MAX_CHAR_SIZE] = {
  {0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0}, 
  {0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0}, 
  {0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0}, 
  {0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0},
  {DASH, DOT, DASH, DOT, DASH, DASH, 0}, //!
  {DOT, DASH, DOT, DOT, DASH, DOT, 0}, //"
  {0, 0, 0, 0, 0, 0, 0},
  {DOT, DOT, DOT, DASH, DOT, DOT, DASH}, //$
  {0, 0, 0, 0, 0, 0, 0},
  {DOT, DASH, DOT, DOT, DOT, 0, 0}, //&
  {DOT, DASH, DASH, DASH, DASH, DOT, 0}, //'
  {DASH, DOT, DASH, DASH, DOT, 0, 0}, //(
  {DASH, DOT, DASH, DASH, DOT, DASH, 0}, //)
  {0, 0, 0, 0, 0, 0, 0},
  {DOT, DASH, DOT, DASH, DOT, 0, 0}, //+
  {DASH, DASH, DOT, DOT, DASH, DASH, 0}, //,
  {DASH, DOT, DOT, DOT, DOT, DASH, 0}, //-
  {DOT, DASH, DOT, DASH, DOT, DASH, 0}, //.
  {DASH, DOT, DOT, DASH, DOT, 0, 0}, ///
  {DASH, DASH, DASH, DASH, DASH, 0, 0}, //0
  {DOT, DASH, DASH, DASH, DASH, 0, 0}, //1
  {DOT, DOT, DASH, DASH, DASH, 0, 0}, //2
  {DOT, DOT, DOT, DASH, DASH, 0, 0}, //3
  {DOT, DOT, DOT, DOT, DASH, 0, 0}, //4
  {DOT, DOT, DOT, DOT, DOT, 0, 0}, //5
  {DASH, DOT, DOT, DOT, DOT, 0, 0}, //6
  {DASH, DASH, DOT, DOT, DOT, 0, 0}, //7
  {DASH, DASH, DASH, DOT, DOT, 0, 0}, //8
  {DASH, DASH, DASH, DASH, DOT, 0, 0}, //9
  {DASH, DASH, DASH, DOT, DOT, DOT, 0}, //:
  {DASH, DOT, DASH, DOT, DASH, DOT, 0}, //;
  {0, 0, 0, 0, 0, 0, 0},
  {DASH, DOT, DOT, DOT, DASH, 0, 0}, //=
  {0, 0, 0, 0, 0, 0, 0},
  {DOT, DOT, DASH, DASH, DOT, DOT, 0}, //?
  {DOT, DASH, DASH, DOT, DASH, DOT, 0}, //@
  {DOT, DASH, 0, 0, 0, 0, 0}, //A
  {DASH, DOT, DOT, DOT, 0, 0, 0}, //B
  {DASH, DOT, DASH, DOT, 0, 0, 0}, //C
  {DASH, DOT, DOT, 0, 0, 0, 0}, //D
  {DOT, 0, 0, 0, 0, 0, 0}, //E
  {DOT, DOT, DASH, DOT, 0, 0, 0}, //F
  {DASH, DASH, DOT, 0, 0, 0, 0}, //G
  {DOT, DOT, DOT, DOT, 0, 0, 0}, //H
  {DOT, DOT, 0, 0, 0, 0, 0}, //I
  {DOT, DASH, DASH, DASH, 0, 0, 0}, //J
  {DASH, DOT, DASH, 0, 0, 0, 0}, //K
  {DOT, DASH, DOT, DOT, 0, 0, 0}, //L
  {DASH, DASH, 0, 0, 0, 0, 0}, //M
  {DASH, DOT, 0, 0, 0, 0, 0}, //N
  {DASH, DASH, DASH, 0, 0, 0, 0}, //O
  {DOT, DASH, DASH, DOT, 0, 0, 0}, //P
  {DASH, DASH, DOT, DASH, 0, 0, 0}, //Q
  {DOT, DASH, DOT, 0, 0, 0, 0}, //R
  {DOT, DOT, DOT, 0, 0, 0, 0}, //S
  {DASH, 0, 0, 0, 0, 0, 0}, //T
  {DOT, DOT, DASH, 0, 0, 0, 0}, //U
  {DOT, DOT, DOT, DASH, 0, 0, 0}, //V
  {DOT, DASH, DASH, 0, 0, 0, 0}, //W
  {DASH, DOT, DOT, DASH, 0, 0, 0}, //X
  {DASH, DOT, DASH, DASH, 0, 0, 0}, //Y
  {DASH, DASH, DOT, DOT, 0, 0, 0}, //Z
  {0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0},
  {DOT, DOT, DASH, DASH, DOT, DASH, 0}, //_
  };

//The setup routine runs once when you press reset:
void setup() 
{                
  //Initialize the digital pin as an output.
  pinMode(led, OUTPUT);
}

//Basic linked-list node implementation 
//Because the size of the user input is unknown, this is easier to use than an array
struct node
{
  char value;
  struct node *next;
};

//The loop routine runs over and over again forever:
void loop() 
{ 
  //Ask the user for the string
  Serial.begin(9600);
  Serial.println("Send text to be displayed in Morse Code. 64 chars max");
  
  //Wait until the user has entered data
  while(Serial.available() == 0){}
  
  //Setup the list
  struct node *head, *currentNode;
  head = (struct node*)malloc(sizeof(struct node));
  head->value = '\0';
  head->next = 0;
  currentNode = head;
  
  //Read the user input
  while(Serial.available() > 0)
  {
    currentNode->value = Serial.read();
    currentNode->next = (struct node*)malloc(sizeof(struct node));
    currentNode = currentNode->next;
    currentNode->next = 0;
  }
  
  //Move currentNode back to the start of the list
  currentNode = head;
  
  Serial.println("Displaying: ");
  
  //Go through all the nodes and display the charachters in Morse Code via the LED
  while(currentNode->next != 0)
  {
    //TODO: Print out each char as text in console as it is being displayed by the LED
    //Serial.print(currentNode->value);
    
    //Get the ASCII value of the charachter being looked at
    int ASCII = currentNode->value;
    
    //Convert lower case letters to upper case
    if(ASCII >= 97 && ASCII <= 122)
    {
      ASCII = ASCII - 32;
    }
    
    //If the charachter is a space
    if(ASCII == 32 ) 
    {
      delay(WORD_SPACE);
    }
    else
      {
        //Go through the timing sequence for each charachter
        for(int i = 0; i < MORSE_MAX_CHAR_SIZE; i++)
        { 
          if(TIMINGS[ASCII][i] == 0)//If the timing sequence is over, break the loop
          {
            break;
          }
          else //Display the timing sequence on the LED
          {
            digitalWrite(led, HIGH);
            delay(TIMINGS[ASCII][i]);
            digitalWrite(led, LOW);
            delay(TIMING_SPACE);
          }
        } 
      }
    
    //Move to the next charachter
    currentNode = currentNode->next;
    delay(CHAR_SPACE);
  }
}

/**
//Ensure the charachter is one that has been programmed in for Morse
  if((userIn[i] >= 32 && userIn[i] <= 34) || userIn[i] == 36 || (userIn[i] >= 38 && userIn[i] <= 41) || (userIn[i] >= 43 && userIn[i] <= 59) 
      || userIn[i] == 61 || (userIn[i] >= 63 && userIn[i] <= 90) || userIn[i] == 95)
**/
        
