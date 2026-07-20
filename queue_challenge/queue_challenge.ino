#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif

static const uint8_t queue_len = 100;
char blinked[]="blinked";
static QueueHandle_t queue1;
static QueueHandle_t queue2;

void startTask1(void *parameter){
  while(1){
    if (Serial.available()){
      String input = Serial.readStringUntil('\n');

      if(input.startsWith("delay ")){
        int delay_time = input.substring(6).toInt();
          if (delay_time > 0){
              if (xQueueSend(queue1,(void*)&delay_time,10)!=pdTRUE){
                Serial.println("Queue full");
              }
          }
      }
      else{
        Serial.println(input);
      }
    }
    vTaskDelay(100/portTICK_PERIOD_MS);
  }
}

void startTask2(void *parameter ){
  while (1){
    static int t =0;
    if(xQueueReceive(queue1,&t,0)==pdTRUE){
      digitalWrite(41,HIGH);
      vTaskDelay(pdMS_TO_TICKS(t));
      digitalWrite(41,LOW);
      vTaskDelay(pdMS_TO_TICKS(t));
      xQueueSend(queue2,blinked,10);
    }
    vTaskDelay(1000/portTICK_PERIOD_MS);
  }
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(41,OUTPUT);
  queue1 = xQueueCreate(queue_len,sizeof(int));
  queue2 = xQueueCreate(10, sizeof(char)*20);
  xTaskCreatePinnedToCore(
    startTask2,
    "task2", 
    2048,
    NULL,
    1,
    NULL,
    app_cpu
  );
  xTaskCreatePinnedToCore(
    startTask1,
    "task1", 
    2048,
    NULL,
    1,
    NULL,
    app_cpu
  );
}

void loop() {

}
