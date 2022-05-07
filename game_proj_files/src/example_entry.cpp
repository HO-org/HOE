#include "hflog.h"

void HOEINIT_AddComponents()
{
    HFLog::GetInstance().Log(HFLog::HF_ERROR, "Hello World!", __FILE__, __LINE__);
}