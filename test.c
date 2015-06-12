/*******************************************************************************
* File Name: AnalogMux.c
* Version 1.80
*
*  Description:
*    This file contains all functions required for the analog multiplexer
*    AMux User Module.
*
*   Note:
*
*******************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#include "AnalogMux.h"

static uint8 AnalogMux_lastChannel = AnalogMux_NULL_CHANNEL;


/*******************************************************************************
* Function Name: AnalogMux_Start
********************************************************************************
* Summary:
*  Disconnect all channels.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void AnalogMux_Start(void) 
{
    uint8 chan;

    for(chan = 0u; chan < AnalogMux_CHANNELS ; chan++)
    {
#if (AnalogMux_MUXTYPE == AnalogMux_MUX_SINGLE)
        AnalogMux_Unset(chan);
#else
        AnalogMux_CYAMUXSIDE_A_Unset(chan);
        AnalogMux_CYAMUXSIDE_B_Unset(chan);
#endif
    }

    AnalogMux_lastChannel = AnalogMux_NULL_CHANNEL;
}


#if (!AnalogMux_ATMOSTONE)
/*******************************************************************************
* Function Name: AnalogMux_Select
********************************************************************************
* Summary:
*  This functions first disconnects all channels then connects the given
*  channel.
*
* Parameters:
*  channel:  The channel to connect to the common terminal.
*
* Return:
*  void
*
*******************************************************************************/
void AnalogMux_Select(uint8 channel) 
{
    AnalogMux_DisconnectAll();        /* Disconnect all previous connections */
    AnalogMux_Connect(channel);       /* Make the given selection */
    AnalogMux_lastChannel = channel;  /* Update last channel */
}
#endif


/*******************************************************************************
* Function Name: AnalogMux_FastSelect
********************************************************************************
* Summary:
*  This function first disconnects the last connection made with FastSelect or
*  Select, then connects the given channel. The FastSelect function is similar
*  to the Select function, except it is faster since it only disconnects the
*  last channel selected rather than all channels.
*
* Parameters:
*  channel:  The channel to connect to the common terminal.
*
* Return:
*  void
*
*******************************************************************************/
void AnalogMux_FastSelect(uint8 channel) 
{
    /* Disconnect the last valid channel */
    if( AnalogMux_lastChannel != AnalogMux_NULL_CHANNEL)
    {
        AnalogMux_Disconnect(AnalogMux_lastChannel);
    }

    /* Make the new channel connection */
#if (AnalogMux_MUXTYPE == AnalogMux_MUX_SINGLE)
    AnalogMux_Set(channel);
#else
    AnalogMux_CYAMUXSIDE_A_Set(channel);
    AnalogMux_CYAMUXSIDE_B_Set(channel);
#endif


    AnalogMux_lastChannel = channel;   /* Update last channel */
}


#if (AnalogMux_MUXTYPE == AnalogMux_MUX_DIFF)
#if (!AnalogMux_ATMOSTONE)
/*******************************************************************************
* Function Name: AnalogMux_Connect
********************************************************************************
* Summary:
*  This function connects the given channel without affecting other connections.
*
* Parameters:
*  channel:  The channel to connect to the common terminal.
*
* Return:
*  void
*
*******************************************************************************/
void AnalogMux_Connect(uint8 channel) 
{
    AnalogMux_CYAMUXSIDE_A_Set(channel);
    AnalogMux_CYAMUXSIDE_B_Set(channel);
}
#endif

/*******************************************************************************
* Function Name: AnalogMux_Disconnect
********************************************************************************
* Summary:
*  This function disconnects the given channel from the common or output
*  terminal without affecting other connections.
*
* Parameters:
*  channel:  The channel to disconnect from the common terminal.
*
* Return:
*  void
*
*******************************************************************************/
void AnalogMux_Disconnect(uint8 channel) 
{
    AnalogMux_CYAMUXSIDE_A_Unset(channel);
    AnalogMux_CYAMUXSIDE_B_Unset(channel);
}
#endif

#if (AnalogMux_ATMOSTONE)
/*******************************************************************************
* Function Name: AnalogMux_DisconnectAll
********************************************************************************
* Summary:
*  This function disconnects all channels.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void AnalogMux_DisconnectAll(void) 
{
    if(AnalogMux_lastChannel != AnalogMux_NULL_CHANNEL) 
    {
        AnalogMux_Disconnect(AnalogMux_lastChannel);
        AnalogMux_lastChannel = AnalogMux_NULL_CHANNEL;
    }
}
#endif

/* [] END OF FILE */
