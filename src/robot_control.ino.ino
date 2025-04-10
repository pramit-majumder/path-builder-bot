// #include <stdio.h>
// #include <math.h>
// #include <stdlib.h>

const int Y = 7;
const int X = 7;

int final_x = 1;
int final_y = 1;

int target_x = 0;
int target_y = 0;

int da = 0, i = 0, j = 0;
int dest_x = 0, dest_y = 0;

bool left, right, front, leftM, rightM, frontM, completed;
int rowise = 1;
int colwise = -1;
int x_way[] = {0,1,0,-1}, y_way[] = {1,0,-1,0};
int x_way_n = 0, y_way_n = 0;

int Matrix[X][Y], row[Y], col[X];

void print_Matrix(){
  for (i = 0; i < Y; i++) {
    for ( j =0; j < X; j++) {
        Serial.print(Matrix[i][j]);
        Serial.print(" ");
      }  
      Serial.println("");
  }
}

//MOTOR FUNCTIONS
void turn90(bool direction){
  if(!direction){//RIGHT
      digitalWrite(5, HIGH);
      digitalWrite(18, LOW);
      digitalWrite(19, LOW);
      digitalWrite(21, HIGH);
      delay(1000/2);
      digitalWrite(5, LOW);
      digitalWrite(18, LOW);
      digitalWrite(19, LOW);
      digitalWrite(21, LOW);
      
  }
  else{
      digitalWrite(5, LOW);
      digitalWrite(18, HIGH);
      digitalWrite(19, HIGH);
      digitalWrite(21, LOW);
      delay(1000/2);
      digitalWrite(5, LOW);
      digitalWrite(18, LOW);
      digitalWrite(19, LOW);
      digitalWrite(21, LOW);
      delay(2000);
  }
}
void change_right(){
  x_way_n = check(x_way_n + 1);
  y_way_n = check(y_way_n + 1);
  rowise = -rowise;
  colwise = -colwise;
  turn90(false);
}
void change_left(){
  x_way_n = check(x_way_n - 1);
  y_way_n = check(y_way_n - 1);
  rowise = -rowise;
  colwise = -colwise;
  turn90(true);
}
void change_forward(){
  digitalWrite(5, HIGH);
  digitalWrite(18, LOW);
  digitalWrite(19, HIGH);
  digitalWrite(21, LOW);
  delay(500);
  digitalWrite(5, LOW);
  digitalWrite(18, LOW);
  digitalWrite(19, LOW);
  digitalWrite(21, LOW);
  Matrix[final_x][final_y] = 0;

  // Serial.print("X: ");
  // Serial.println(final_x + x_way[x_way_n]);
  // Serial.print("Y: ");
  // Serial.println(final_y + y_way[y_way_n]);
  // Serial.println();
  // Serial.println(final_x + x_way[x_way_n] != 0);
  // Serial.println(final_x + x_way[x_way_n] != X - 1);
  // Serial.println(final_y + y_way[y_way_n] != 0);
  // Serial.println(final_y + y_way[y_way_n] != Y - 1);
  Matrix[final_x][final_y] = 7;
  if(final_x + x_way[x_way_n] != 0 && final_y + y_way[y_way_n] != 0 && final_x + x_way[x_way_n] != X - 1  && final_y + y_way[y_way_n] != Y - 1){
    final_x += x_way[x_way_n];
    final_y += y_way[y_way_n];
    Matrix[final_x][final_y] = 1;
  }
  else{
    Serial.println("Cannot Move sir");
    Matrix[final_x][final_y] = 1;
  }
}

//LOOKERS
bool look_right(int x_, int y_){
  int x_right = (x_ + x_way[check(x_way_n + 1)]);
  int y_right = (y_ + y_way[check(y_way_n + 1)]);
  Serial.print("Right map: ");
  Serial.println(Matrix[x_right][y_right]);
  if(right == false && Matrix[x_right][y_right] == 0){
    Matrix[x_right][y_right] = 5;
    right = true;
  }
  if((Matrix[x_right][y_right] == 0) /*|| Matrix[x_right][y_right] != 5 || Matrix[x_right][y_right] != 7*/){
    return true;
  }
  else{
    return false;
  }
}
bool look_left(int x_, int y_){
  int x_left = (x_ + x_way[check(x_way_n - 1)]);
  int y_left = (y_ + y_way[check(y_way_n - 1)]);
  Serial.print("Left map: ");
  Serial.println(Matrix[x_left][y_left]);
  if(left == false && Matrix[x_left][y_left] == 0){
    Matrix[x_left][y_left] = 5;
    left = true;
  }
  if((Matrix[x_left][y_left] == 0/*|| Matrix[x_left][y_left]*/)){
    return true;
  }
  else{
    return false;
  }
}
bool look_forward(int x_, int y_){
  int x_front = (x_ + x_way[check(x_way_n)]);
  int y_front = (y_ + y_way[check(y_way_n)]);
  Serial.print("Front map: ");
  Serial.println(Matrix[x_front][y_front]);

  if(front == false && Matrix[x_front][y_front] == 0){
    Matrix[x_front][y_front] = 5;
    front = true;
  }

  if(Matrix[x_front][y_front] == 0  /*|| Matrix[x_front][y_front] != 5 || Matrix[x_front][y_front] != 7*/){


    return true;
  }
  else{
    return false;
  }
}


int find_zeroes(){
  Serial.println("asdas");
  int occurance = find_occurance();
  int targets[occurance][2];
  int counter = 0;
  for (i = 0; i < X; i++) {
    for (j = 0; j < Y; j++) {
      if (Matrix[i][j] == 0) {
        targets[counter][0] = i;
        targets[counter][1] = j;
        counter++;
        Serial.print("Found Targets");Serial.println(X);Serial.println(Y);
      }
    }
  }
  if(occurance > 0){
    int x_ = targets[0][0], y_ = targets[0][1];
    double d = distance(targets[0][0], targets[0][1], final_x, final_y);
    for(int i = 1; i < occurance; i++){
      Serial.println(d);
      Serial.println(distance(targets[i][0], targets[i][1], final_x, final_y)); 
      if(0 < (d - distance(targets[i][0], targets[i][1], final_x, final_y))){
        d = distance(targets[i][0], targets[i][1], final_x, final_y);
        x_ = targets[i][0];
        y_ = targets[i][1];
      }

    }
    dest_x = x_;
    dest_y = y_;
    da = 0;
    find_pathway();
  }
}
int find_occurance(){
  int count = 0;
  for (i = 1; i < X - 1; i++) {
    for (j = 1; j < Y - 1; j++) {
      if (Matrix[i][j] == 0) {
        count++;
      }
    }
  }
  return count;
}

double distance(int x1, int y1, int x2, int y2){
  double d = ((x2 - x1)* (x2 - x1)) + ((y2 - y1)*(y2 - y1));
  return sqrt(d);
}

void find_pathway(){
  da == 0;
  if(final_x < dest_x){
    int difx = abs(final_x - dest_x);
    int dify = abs(final_y - dest_y);
    for(int i = 1; i <= difx; i++){
      if(!closed_space(final_x+i, final_y)){
        Matrix[final_x + i][final_y] = 0;
      }
    }
    print_Matrix();
  }
  Serial.println("FOUND");
}

//checkers
bool closed_space(int x, int y){
  return !(look_right(x,y) || look_left(x,y) || look_forward(x,y));
}
int check(int x){
  if(x == 4){
    return 0;
  }
  else if(x == -1){
    return 3;
  }
  return x;
}
long measureDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  long duration = pulseIn(echoPin, HIGH);
  return (duration * 0.034 / 2);
}
bool dataPoint() {
    // Iterate over each row
    for (i = 0; i < X; i++) {
        // Iterate over each column
        for (j = 0; j < Y; j++) {
            if (Matrix[i][j] == 0) {
  
                return true; // Exit once the element is found
            }
        }
    }
    return false;
}


void setup() {
  
  pinMode(13, OUTPUT);
  pinMode(12, INPUT);
  pinMode(14, OUTPUT);
  pinMode(27, INPUT);
  pinMode(26, OUTPUT);
  pinMode(25, INPUT);

  pinMode(5, OUTPUT);
  pinMode(18, OUTPUT);
  pinMode(19, OUTPUT);
  pinMode(21, OUTPUT);
  

  pinMode(22, OUTPUT);
  pinMode(23, OUTPUT);
  analogWrite(22, 155);
  analogWrite(23, 155); 
  int y = 1;
  for (i = 0; i < Y; i++) {
      for (j =0; j < X; j++) {
            if(j == 0 || j == X - 1 || i == 0 || i == Y - 1){
                Matrix[i][j] = 5;
            }
            else{
                Matrix[i][j] = 0;
                y++;
            }
      }
  }
  Matrix[final_x][final_y] = 1;
  Serial.begin(115200);
  
}

//OPERATIONS
void check_next_step(){
  // if(Matrix[final_x + x_way[x_way_n]][final_y + y_way[y_way_n]] == 5){
    leftM = look_left(final_x, final_y);
    frontM = look_forward(final_x, final_y);
    rightM = look_right(final_x, final_y);
    
    if(leftM == false){
        if(frontM == false){
            if(rightM == false){
                Serial.println("REVERSE");//if LEFT RIGHT AND FRONT ARE FALSE
                change_right();
                change_right();
                if(da == 2){
                  find_zeroes();
                }
                da++;
                delay(2000);
            }
            else{
                Serial.println("TURN RIGHT");// IF LEFT AND FRONT ARE FALSE
                change_right();  
                      
            }
        }
        else{
            Serial.println("GO FRONT");// IF RIGHT AND LEFT ARE FALSE
    
        }
    }
    else{
        if(frontM == false){
            if(rightM == false){
                Serial.println("TURN LEFT");//IF RIGHT AND FRONT ARE FALSE
                change_left();
        
            }
            else{
                Serial.println("THE OPTIMAL WAY");// IF ONLY FRONT IS FALSE
                change_left();
            }
        }
        else{
            Serial.println("CONTINUE AS NORMAL");// IF FRONT IS NOT FALSE
    
        }
    }
}
void get_row(){
  for(i = 0;i < Y; i++){
    row[i] = Matrix[final_x][i];
  }
}
void get_column(){
  for(i = 0;i < X; i++){
    col[i] = Matrix[i][final_y];
  }
}


void loop() {
  check_next_step();
  change_forward();

  print_Matrix();
    // Serial.println("Recording data");
    
  long leftd = measureDistance(26, 25);
  if((leftd <= 10)){
    Serial.println("LEFT BLOCKED");
    left = false;
  }
  long rightd = measureDistance(14, 27);
  long frontd = measureDistance(13, 12);
  if((rightd <= 10)){
    Serial.println("RIGHT BLOCKED");
    right = false;
  }
  if((frontd <= 20)){
    Serial.println("FRONT BLOCKED");
    front = false;
  }
  Serial.println("\nRECORDED");
  delay(1000);
  Serial.println(leftd);
  Serial.println(rightd);
  Serial.println(frontd );

   //  //d ete 

}