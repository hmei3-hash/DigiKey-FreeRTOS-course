#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif
const char msg[] = "hellooooooo";

void startTask1(void *parameter)
{
    while (1)
    {
      int a =1;
      int b[100];
      for(int i=0; i<100;i++){
        b[i]=a+1;

      }
      //Serial.println(b[0]);

      //print out reamaining stack memory
    Serial.print("High water mark (words): ");
    Serial.println(uxTaskGetStackHighWaterMark(NULL));

    //print out number of free heap memory bytes before malloc
    Serial.print("Heap before malloc (bytes): ");
    Serial.println(xPortGetFreeHeapSize());
    int *ptr = (int*)pvPortMalloc(1024*sizeof(int));

    if(ptr==NULL){
      Serial.println("Not enough heap");
    }
    else{
      for (int i=0; i<1024;i++){
      ptr[i]=3;
    }
    }
    Serial.print("Heap after malloc (bytes): ");
    Serial.println(xPortGetFreeHeapSize());
    vPortFree(ptr);
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
}

void loop() {
  // put your main code here, to run repeatedly:

}
