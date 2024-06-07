#include "voice_command.h"

volatile bool pdm_pcm_flag = false;
static int16_t pdm_pcm_ping[FRAME_SIZE] = {0};
static int16_t pdm_pcm_pong[FRAME_SIZE] = {0};
static int16_t *pdm_pcm_buffer = &pdm_pcm_ping[0];

cyhal_pdm_pcm_t pdm_pcm;
cyhal_clock_t   audio_clock;
cyhal_clock_t   pll_clock;

const cyhal_pdm_pcm_cfg_t pdm_pcm_cfg =
{
		.sample_rate     = SAMPLE_RATE_HZ,
		.decimation_rate = DECIMATION_RATE,
		.mode            = CYHAL_PDM_PCM_MODE_LEFT,
		.word_length     = 16,  /* bits */
		.left_gain       = CYHAL_PDM_PCM_MAX_GAIN,   /* dB */
		.right_gain      = CYHAL_PDM_PCM_MAX_GAIN,   /* dB */
};

void voice_command_play(){
	uint64_t uid;

	cyhal_pdm_pcm_init(&pdm_pcm, PDM_DATA, PDM_CLK, &audio_clock, &pdm_pcm_cfg);
	cyhal_pdm_pcm_register_callback(&pdm_pcm, pdm_pcm_isr_handler, NULL);
	cyhal_pdm_pcm_enable_event(&pdm_pcm, CYHAL_PDM_PCM_ASYNC_COMPLETE, CYHAL_ISR_PRIORITY_DEFAULT, true);
	cyhal_pdm_pcm_start(&pdm_pcm);
	cyhal_pdm_pcm_read_async(&pdm_pcm, pdm_pcm_buffer, FRAME_SIZE);

	uid = Cy_SysLib_GetUniqueId();
	printf("uniqueIdHi: 0x%08lX, uniqueIdLo: 0x%08lX\r\n", (uint32_t)(uid >> 32), (uint32_t)(uid << 32 >> 32));

	if(!cyberon_asr_init(asr_callback))
	{
		while(1);
	}

    while(1)
    {
        if(pdm_pcm_flag)
        {
            pdm_pcm_flag = 0;
            cyberon_asr_process(pdm_pcm_buffer, FRAME_SIZE);
        }
    }
}

static void pdm_pcm_isr_handler(void *arg, cyhal_pdm_pcm_event_t event)
{
    static bool ping_pong = false;

    (void) arg;
    (void) event;

    if(ping_pong)
    {
        cyhal_pdm_pcm_read_async(&pdm_pcm, pdm_pcm_ping, FRAME_SIZE);
        pdm_pcm_buffer = &pdm_pcm_pong[0];
    }
    else
    {
        cyhal_pdm_pcm_read_async(&pdm_pcm, pdm_pcm_pong, FRAME_SIZE);
        pdm_pcm_buffer = &pdm_pcm_ping[0];
    }

    ping_pong = !ping_pong;
    pdm_pcm_flag = true;
}

void clock_init(void)
{
	cyhal_clock_reserve(&pll_clock, &CYHAL_CLOCK_PLL[0]);
    cyhal_clock_set_frequency(&pll_clock, AUDIO_SYS_CLOCK_HZ, NULL);
    cyhal_clock_set_enabled(&pll_clock, true, true);

    cyhal_clock_reserve(&audio_clock, &CYHAL_CLOCK_HF[1]);

    cyhal_clock_set_source(&audio_clock, &pll_clock);
    cyhal_clock_set_enabled(&audio_clock, true, true);
}

static void asr_callback(const char *function, char *message, char *parameter)
{
	printf("[%s]%s(%s)\r\n", function, message, parameter);
}
