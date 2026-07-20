#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif

static TaskHandle_t task1 = NULL;
static TaskHandle_t task2 = NULL;
volatile int intensity = 50;
#define ledPin 15

void startTask1(void *parameter)
{
    while (1)
    {
        if (Serial.available() > 0)
        {
            int val = Serial.parseInt();

            if (val >= 0 && val <= 255)
            {
                intensity = val;
            }

            Serial.println(intensity);
            while (Serial.available())
                Serial.read();
        }

        vTaskDelay(pdMS_TO_TICKS(10));
    }
}
void startTask2(void *parameter)
{
    while (1)
    {
        analogWrite(ledPin,intensity);

        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  pinMode(ledPin, OUTPUT);
  vTaskDelay(1000/portTICK_PERIOD_MS);


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
