#ifdef ENABLE_DEBUG_LOG
#define SERIAL_LOG(x) Serial.println(x);
#else
#define SERIAL_LOG(x)
#endif