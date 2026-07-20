#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif
const char msg[] = "hellooooooo";

static TaskHandle_t task1 = NULL;
static TaskHandle_t task2 = NULL;

void startTask1(void *parameter)
{
    while (1)
    {
        int len = strlen(msg);

        for (int i = 0; i < len; i++)
        {
            Serial.print(msg[i]);
        }

        Serial.println();

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
void startTask2(void *parameter)
{
    while (1)
    {
        Serial.print("*");

        vTaskDelay(pdMS_TO_TICKS(100));
    }
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(300);


  vTaskDelay(1000/portTICK_PERIOD_MS);
  Serial.println();
  Serial.println("-------FreeRTOS Task Demo--------");

  Serial.print("Setup and loop are running on core");
  Serial.println(xPortGetCoreID());

  xTaskCreatePinnedToCore(
    startTask1,
    "Task1", 
    1024,
    NULL,
    1,
    &task1,
    app_cpu
  );

  xTaskCreatePinnedToCore(
    startTask2,
    "Task2", 
    1024,
    NULL,
    2,
    &task2,
    app_cpu
  );
}

void loop() {
  // put your main code here, to run repeatedly:

}
