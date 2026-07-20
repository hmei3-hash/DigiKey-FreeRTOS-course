#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif

static const uint8_t msg_queue_len = 5;

static QueueHandle_t msg_queue;

void printMsg(void *parameter ){
  int item;

  while (1){
    if (xQueueReceive(msg_queue, (void*)&item,0)==pdTRUE){
      Serial.println(item);
    }
    vTaskDelay(1000/portTICK_PERIOD_MS);
  }
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  msg_queue = xQueueCreate(msg_queue_len,sizeof(int));
  xTaskCreatePinnedToCore(
    printMsg,
    "Print Message", 
    1024,
    NULL,
    1,
    NULL,
    app_cpu
  );
}

void loop() {
  // put your main code here, to run repeatedly:
  static int num = 0;

  if (xQueueSend(msg_queue,(void*)&num,10)!=pdTRUE){
    Serial.println("Queue full");
  }
  num++;
  vTaskDelay(500/portTICK_PERIOD_MS);
}
