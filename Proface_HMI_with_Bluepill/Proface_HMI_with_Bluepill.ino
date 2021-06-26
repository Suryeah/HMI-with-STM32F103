#include <stdlib.h>

#define LED PC13

String txtMsg = "";
char s;
uint32_t FQ, FQ1, FQ2, SFQ, EFQ, F_STEP = 0;
uint32_t REP, DELAY;
uint16_t SPSK, EPSK;
float ASF = 0.99994;       //  AMPLITUDE CONTROL FOR DDS1(0.1-1)
float SA, EA = 0;
bool INFI = 0;
uint32_t  T1, T2 = 0;
float A_STEP = 0;
float testVar = 0.20;

void setup() {
  Serial.begin(115200);
  Serial3.begin(115200);
  pinMode(LED, OUTPUT);
}

void loop()
{
  while (Serial3.available() > 0)
  {
    txtMsg = Serial3.readStringUntil('\n');
    Serial.println(txtMsg);

    switch (txtMsg[0])
    {
      case 'a':    /* MONO Tone */
        {
          FQ, ASF = 0;
          FQ = txtMsg.substring(2, 11).toInt();
          ASF = txtMsg.substring(12, 16).toFloat();
          txtMsg = "";
          blinkL();
          mono_Tone();
        } break;

      case 'b':     /* Freq Sweep */
        {
          SFQ, ASF, EFQ = 0;
          SFQ = txtMsg.substring(2, 11).toInt();
          EFQ = txtMsg.substring(12, 21).toInt();
          F_STEP = txtMsg.substring(22, 31).toInt();
          DELAY = txtMsg.substring(32, 37).toInt();
          ASF = txtMsg.substring(38, 42).toFloat();
          REP = txtMsg.substring(43, 47).toInt();
          if (REP == 0)
            INFI = 1;
          else
            INFI = 0;
          txtMsg = "";
          freq_Sweep();
        } break;

      case 'c':     /* Amplitude Sweep */
        {
          SA = txtMsg.substring(2, 6).toFloat();
          EA = txtMsg.substring(7, 11).toFloat();
          A_STEP = txtMsg.substring(12, 16).toFloat();
          DELAY = txtMsg.substring(17, 22).toInt();
          FQ = txtMsg.substring(23, 32).toInt();
          REP = txtMsg.substring(33, 37).toInt();
          if (REP == 0)
            INFI = 1;
          else
            INFI = 0;
          txtMsg = "";
          amp_Sweep();
        } break;

      case 'd':       /* FSK */
        {
          FQ1 = txtMsg.substring(2, 11).toInt();
          FQ2 = txtMsg.substring(12, 21).toInt();
          T1 = txtMsg.substring(22, 25).toInt();
          T2 = txtMsg.substring(26, 29).toInt();
          ASF = txtMsg.substring(30, 34).toFloat();
          REP = txtMsg.substring(35, 39).toInt();

          if (REP == 0)
          {
            INFI = 1;
            // Serial.println("INFI SET");
          }
          else
          {
            INFI = 0;
            // Serial.println("INFI SET");
          }
          txtMsg = "";
          FSK();
        } break;

      case 'e':    /* ASK */
        {
          SA = txtMsg.substring(2, 6).toFloat();
          EA = txtMsg.substring(7, 11).toFloat();
          T1 = txtMsg.substring(12, 15).toFloat();
          T2 = txtMsg.substring(16, 21).toInt();
          FQ = txtMsg.substring(22, 31).toInt();
          REP = txtMsg.substring(32, 36).toInt();

          if (REP == 0)
          {
            INFI = 1;
            //Serial.println("INFI SET");
          }
          else
          {
            INFI = 0;
            //Serial.println("INFI SET");
          }
          txtMsg = "";
          ASK();
        } break;

      case 'f':    /* PSK */
      {
        SPSK = txtMsg.substring(2, 5).toInt();
        EPSK = txtMsg.substring(6, 9).toInt();
        T1 = txtMsg.substring(10, 13).toInt();
        T2 = txtMsg.substring(14, 17).toInt();
        FQ = txtMsg.substring(18, 27).toInt();
        ASF = txtMsg.substring(28, 32).toFloat();
        REP = txtMsg.substring(33, 37).toInt();
        PSK();
      }break;

      case 's':
        {
          Stop();
        } break;

      default:
        txtMsg = "";
    }
  }
}

void mono_Tone()
{
  Serial.println("FQ:  " + String(FQ));
  Serial.println("ASF:  " + String(ASF));
  if ((FQ) && (ASF))
    Serial3.println("yes");
  else
    Serial3.println("No");
}

void freq_Sweep()
{
  Serial.println("SFQ:  " + String(SFQ));
  Serial.println("EFQ:  " + String(EFQ));
  Serial.println("F_STEP:  " + String(F_STEP));
  Serial.println("DELAY:  " + String(DELAY));
  Serial.println("ASF:  " + String(ASF));
  Serial.println("REP:  " + String(REP));
  if ((SFQ) && (SFQ) && (F_STEP) && (DELAY))
    Serial3.println("yes");
  else
    Serial3.println("No");
}

void amp_Sweep()
{
  Serial.println("SA: " + String(SA));
  Serial.println("EA:  " + String(EA));
  Serial.println("A_STEP: " + String(A_STEP));
  Serial.println("DELAY:  " + String(DELAY));
  Serial.println("FQ:  " + String(FQ));
  Serial.println("REP:  " + String(REP));
  if ((SA) && (EA) && (A_STEP) && (DELAY) && (FQ))
    Serial3.println("yes");
  else
    Serial3.println("No");
}

void FSK()
{
  Serial.println("FQ1:  " + String(FQ1));
  Serial.println("FQ2:  " + String(FQ2));
  Serial.println("T1:  " + String(T1));
  Serial.println("T2:  " + String(T2));
  Serial.println("ASF:  " + String(ASF));
  Serial.println("REP:  " + String(REP));
  Serial3.println("yes");
}

void ASK()
{
  Serial.println("SA:  " + String(SA));
  Serial.println("EA:  " + String(EA));
  Serial.println("T1:  " + String(T1));
  Serial.println("T2:  " + String(T2));
  Serial.println("ASF:  " + String(ASF));
  Serial.println("FQ:  " + String(FQ));
  Serial.println("REP:  " + String(REP));
  if ((SA) && (EA) && (T1) && (T2) && (FQ) && (ASF))
    Serial3.println("yes");
  else
    Serial3.println("No");
}

void PSK()
{
  Serial.println("SPSK:  " + String(SPSK));
  Serial.println("EPSK:  " + String(EPSK));
  Serial.println("T1:  " + String(T1));
  Serial.println("T2:  " + String(T2));
  Serial.println("FQ:  " + String(FQ));
  Serial.println("ASF:  " + String(ASF));
  Serial.println("REP:  " + String(REP));
  if ((SPSK) && (EPSK) && (T1) && (T2) && (FQ) && (ASF))
    Serial3.println("yes");
  else
    Serial3.println("No");
}

void Stop()
{
  Serial.println("STOPPED");
  Serial3.println("off");
}

void blinkL()
{
  for (int i = 0; i < 3; i++)
  {
    digitalWrite(LED , HIGH);
    delay(500);
    digitalWrite(LED , LOW);
    delay(500);
  }
}
