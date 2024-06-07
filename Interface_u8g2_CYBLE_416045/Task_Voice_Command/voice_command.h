#ifndef VOICE_COMMAND_H_
#define VOICE_COMMAND_H_

#include "cyhal.h"
#include "cybsp.h"
#include "cy_retarget_io.h"
#include "stdlib.h"

#include "cyberon_asr.h"

#define FRAME_SIZE                  (480u)
#define SAMPLE_RATE_HZ              (16000u)
#define DECIMATION_RATE             (96u)
#define AUDIO_SYS_CLOCK_HZ          (24576000u)
#define PDM_DATA                    (P10_5)
#define PDM_CLK                     (P10_4)

static void pdm_pcm_isr_handler(void *arg, cyhal_pdm_pcm_event_t event);
void clock_init(void);

static void asr_callback(const char *function, char *message, char *parameter);
void voice_command_play();

#endif
