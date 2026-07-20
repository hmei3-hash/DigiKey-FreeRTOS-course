#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif
volatile char msg[100];
volatile bool ready =false;
void startTask1(void *parameter)
{
    while (1)
    {
        if (ready)
        {
            Serial.print("Received: ");
            Serial.println((char *)msg);

            ready = false;
        }

        vTaskDelay(100/portTICK_PERIOD_MS);
    }
}

void startTask2(void *parameter)
{
    while (1)
    {
      int idx =0;
     while (Serial.available()){
      char c = Serial.read();
      msg[idx]=c;
      idx++;
      if (c == '\n') {
        msg[idx] = '\0';
        ready = true;
        vTaskDelay(100/portTICK_PERIOD_MS);
        idx = 0;
     }
    }
    vTaskDelay(100/portTICK_PERIOD_MS);
}
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  vTaskDelay(1000/portTICK_PERIOD_MS);
  Serial.println();
  Serial.println("-------FreeRTOS Task Demo--------");
  Serial.print("Setup and loop are running on core");
  Serial.println(xPortGetCoreID());
  xTaskCreatePinnedToCore(
    startTask1,
    "Task1", 
    2048,//1024 caused a overflow
    NULL,
    1,
    NULL,
    app_cpu
  );
  xTaskCreatePinnedToCore(
    startTask2,
    "Task2", 
    1024,
    NULL,
    2,
    NULL,
    app_cpu
  );
}

void loop() {
  // put your main code here, to run repeatedly:

}
