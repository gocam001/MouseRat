#include <FreeRTOS_ARM.h>
#include <MR_PID.h>

static void getSpeedTask(void* arg) {
  getSpeed_Init();
  while (1) {
    getSpeed_Tick();
    vTaskDelay((10L * configTICK_RATE_HZ) / 1000L);
  }
}

static void ePIDTask(void* arg) {
  ePID_Init();
  while (1) {
    ePID_Tick();
    vTaskDelay((10L * configTICK_RATE_HZ) / 1000L);
  }
}

static void SetTask(void* arg) {
  Set_Init();
  while (1) {
    Set_Tick();
    vTaskDelay((10L * configTICK_RATE_HZ) / 1000L);
  }
}

void setup() {
  xTaskCreate(getSpeedTask, NULL, configMINIMAL_STACK_SIZE, NULL, 1, NULL);
  xTaskCreate(ePIDTask, NULL, configMINIMAL_STACK_SIZE, NULL, 1, NULL);
  xTaskCreate(SetTask, NULL, configMINIMAL_STACK_SIZE, NULL, 1, NULL);
  vTaskStartScheduler();
  Serial.println(F("Insufficient RAM"));
  while(1);
}

void loop() {}
