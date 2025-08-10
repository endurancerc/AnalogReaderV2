/*********************************************************************
 *
 *                13 analog inputs & 16 digital inputs
 *                 
 *
 *********************************************************************/

#define DEVICE_SENDDATA_SIZE		28	//(13analog+2digital)
//#define DEVICE_SENDDATA_SIZE		18	//(8analog+2ditital)
#define DEVICE_DESCTABLE_SIZE		57
//#define DEVICE_DESCTABLE_SIZE		65

#ifndef USER_H
#define USER_H

/** P U B L I C  P R O T O T Y P E S *****************************************/
void UserInit(void);
void ProcessIO(void);

#endif //USER_H
