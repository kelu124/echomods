/***
 * File: patch_keil.c
 * porting iar project to keil, something need to do.
 *
 * Created by JerryYu @ Jan 13rd,2015
 * Ver: 0.1
 * */


#if defined(__CC_ARM)

struct mxchip_mallinfo *mxchip_memory_info(void);

struct mxchip_mallinfo* mico_memory_info(void)
{
    return mxchip_memory_info();
}

#endif 

