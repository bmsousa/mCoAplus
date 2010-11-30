//
// Copyright (C) 2007 
// Faqir Zarrar Yousaf
// Communication Networks Institute, Dortmund University of Technology (TU Dortmund), Germany.
// Christian Bauer
// Institute of Communications and Navigation, German Aerospace Center (DLR)
//
// Copyright (C) 2007 
// Bruno Sousa
// Laboratory  Communications and Telematics (LCT) University of Coimbra, Portugal
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
//



cplusplus {{  
#include "INETDefs.h"
#include "IPv6Address.h"
#include "IPv6Datagram.h" // added by CB
#include "IPv6ExtensionHeaders.h" // 17.10.07 - CB
#include "KeyMCoABind.h" //Bruno Sousa
}}


class noncobject IPv6Address;

class noncobject IPv6ExtensionHeader;

class noncobject IPv6DestinationOptionsHeader;

class noncobject KeyMCoABind;

//Bruno Sousa 
//?




///////////////////////////////////////////
// Bruno Sousa 2010/4/29
///////////////////////////////////////////

// Mobility Options
enum MobOpts{
OPTION_PAD1  						=0;
OPTION_PADN  						=1;
OPTION_BINDING_REFRESH_ADVICE  		=2;
OPTION_ALTERNATE_CARE_OF_ADDRESS  	=3;
OPTION_NONCES_INDICES  				=4;
OPTION_BINDING_AUTHORIZATION_DATA  	=5;
OPTION_HOME_ADDRESS  				=201;

OPTION_BINDING_IDENTIFIER_MOBILITY  =135 ;   
    
}

enum MobOptsPayloadLen{
    LEN_MOBOPTS_HEADER_FIELDS	= 	 2; //Length of Type and length fields (16 bits)
 	LEN_BINDING_REFRESH_ADVICE 	=    4; //(32)/8;
 	LEN_NONCE_INDICES			=    4;
 	LEN_BINDING_AUTHORIZATION_DATA =   14; //(96+16)/8;
 	LEN_BID_NO_COA					=    6;   //(16+32)/8 wtihout CoA
 	LEN_BID_WITH_COA				= 	22;   //(16+32+128)/8
}

// To represent A mobility Option
class MobOption{
    //@customize(true);
	unsigned int mobOptionType enum(MobOpts);
	unsigned int mobOptionLength;
	
	int payloadLength; //TODO: Fixme: Correctly this hould not be like this...
	    
}




//Bruno Sousa 2010/4/10
// RFC 3775
//
// 6.2.4.  Binding Refresh Advice
// The Binding Refresh Advice option has an alignment requirement of 2n.
//
class  MobOption_Binding_RefreshAdvice extends MobOption {
    //@customize(true);
 	unsigned int  refreshInterval;   
 	
 
}

// 6.2.6. Nonce Indices
//   The Nonce Indices option has an alignment requirement of 2n. 
class MobOption_Nonce_Indices extends MobOption {
    //@customize(true);
 	int home_nonce_index;
 	int care_of_nonce_index;
 	   
}

// 6.2.7.  Binding Authorization Data
//
//   The Binding Authorization Data option does not have alignment
//   requirements as such.  However, since this option must be the last
//   mobility option, an implicit alignment requirement is 8n + 2.
//
class  MobOption_Binding_AuthorizationData extends MobOption{
	//@customize(true);
	int authenticator; // First 96 bits of algorithm HMAC_SHA1
	
	
}



// RFC5648
//
//4.3.  Binding Identifier Mobility Option

// The Binding Identifier mobility option is included in the Binding
//  Update, Binding Acknowledgement, Binding Refresh Request, and Care-of
// Test Init and Care-of Test messages.  The Binding Identifier mobility
//   option has an alignment requirement of 2n if the Care-of Address
//   field is not present.  Otherwise, it has the alignment requirement of
//   8n + 2.
//
class  MobOption_Binding_Identifier_Mobility extends MobOption
{
 

	//unsigned int BindingID;
	unsigned int Reserved;
	unsigned int Status;
	bool HFlag;
	//IPv6Address CoA;
	KeyMCoABind kMCoA;
	
	
}



// To represent the different mobility BID Options
class MobilityBIDOptions{
//	@customize(true);
	MobOption_Binding_Identifier_Mobility  mobOpts[];
}










enum MobilityHeaderType
{

    BINDING_REFRESH_REQUEST = 0;
    HOME_TEST_INIT = 1;
    CARE_OF_TEST_INIT = 2;
    HOME_TEST = 3;
    CARE_OF_TEST = 4;
    BINDING_UPDATE = 5;
    BINDING_ACKNOWLEDGEMENT = 6;
    BINDING_ERROR = 7;
}

packet MobilityHeader // extends IPv6ExtensionHeader // TODO check how to define MobilityHeader as subclass of IPv6ExtensionHeader
{
    int mobilityHeaderType enum(MobilityHeaderType);
}




packet BindingUpdate extends MobilityHeader
{
    unsigned int lifetime;
    unsigned int sequence;
    bool ackFlag;				//A-Flag (Acknowledge Flag)
    bool homeRegistrationFlag;		//H-Flag (Home Registration Flag)
    bool linkLocalAddressCompatibilityFlag;	//L-Flag (Link Local Address Compatibility Flag)
    bool keyManagementFlag = false;		//K-Flag (Key Management Flag)
    
    //Added for MCoA 
    // see:http://www.iana.org/assignments/mobility-parameters/
    bool mapHMIPv6Flag;					// M-flag RFC4140
    bool mobRouterFlag;					// R-flag RFC 3963
    bool proxyRegistrationFlag;			// P-flag RFC5213 (PMIPv6)
    bool forceUDPencap;					// F-flag RFC5555
    bool tunnelGREflag;					// T-flag RFC-ietf-netlmm-grekey-option-09
    bool overwriteFlag;					// O-flag RFC5638 (Overwrite Flag)
    
    //Mobility Options not defined - MODIFIED Bruno Sousa
    IPv6Address homeAddressMN;		//As BU is supposed to be sent with Home Address Option, therefore i make this part of BU Msg.

    // for CN communication; value different from 0 shows that it is used
    int bindingAuthorizationData = 0; // 28.08.07 - CB
    
    // Add mobility Options - Bruno Sousa 2010/4/29
    //MobilityOptions mobOpts; /// The most efficient and scalable solution was to have a vector od mobility Options instead of indivudal vectors.
 
 	MobOption_Binding_AuthorizationData mobBindingAuthorization; //only once
 	
 	MobOption_Binding_Identifier_Mobility mobBIDmobility[]; 
   
}


//Defining the status fields for the Binding Acknowledgement Message

enum BAStatus
{

    BINDING_UPDATE_ACCEPTED = 0;
    BU_ACCEPT_BUT_DISCOVER_PREFIX = 1;
    REASON_UNSPECIFIED = 128;
    ADMINISTRATIVELY_PROHIBITED = 129;
    INSUFFICIENT_RESOURCES = 130;
    HOME_REGISTRATION_NOT_SUPPORTED = 131;
    NOT_HOME_SUBNET = 132;
    NOT_HA_FOR_THIS_MN = 133;
    DAD_FAILED = 134;
    SEQUENCE_NUMBER_OUT_OF_WINDOW = 135;
    EXPIRED_HOME_NONCE_INDEX = 136;
    EXPIRED_CARE_OF_NONCE_INDEX = 137;
    EXPIRED_NONCES = 138;
    REGISTRATION_TYPE_CHANGE_DISALLOWED = 139;
    
    //add by Logan Apr 27, 2010
    
	MCOA_NOTCOMPLETE 				     			=	4;
	MCOA_RETURNHOME_WO_NDP 							=	5;
	MCOA_MALFORMED 									=	164;
	MCOA_NON_MCOA_BINDING_EXISTS 					=	165;
	MCOA_UNKOWN_COA 								=	167;
	MCOA_PROHIBITED 								=	166;
	MCOA_BULK_REGISTRATION_PROHIBITED 				=	168;
	MCOA_SIMULTANEOUS_HOME_AND_FOREIGN_PROHIBITED 	=	169;
    
    
}

//==================Defining Binding Acknowledgement Message===================

packet BindingAcknowledgement extends MobilityHeader
{
    int status enum(BAStatus);
    unsigned int sequenceNumber;
    unsigned int lifetime;
    bool keyManagementFlag = false;//K-Flag (Key Management Flag)
	//Mobility Options not defined

    // for CN communication; value different from 0 shows that it is used
    int bindingAuthorizationData = 0; // 28.08.07 - CB
    
    //Bruno Sousa 2010/4/30 
    // Add mobility Options
    MobOption_Binding_RefreshAdvice mobBindingRefreshAdvice;
    
    MobOption_Binding_AuthorizationData mobBindingAuthorization;
    
    MobOption_Binding_Identifier_Mobility mobBIDmobility[]; 
}

//==================Defining Binding Error Status====================

enum BEStatus
{

    UNKNOWN_BINDING_FOR_HOME_ADDRESS_DEST_OPTION = 1;
    UNKNOWN_MH_TYPE = 2; //Unrecognised MH Type
}

//==================Defining Binding Error Message===================

packet BindingError extends MobilityHeader
{
    int status enum(BEStatus);
    IPv6Address homeAddress;
	//Mobility Options not defined

}

//=============Message definition of Home Test Init Message ==========

packet HomeTestInit extends MobilityHeader
{
    unsigned int homeInitCookie;
    
    MobOption_Binding_Identifier_Mobility mobBIDmobility[];
    
}

//=============Message definition of Home Test Message ==========

packet HomeTest extends MobilityHeader
{
    unsigned int homeInitCookie;
    unsigned int homeKeyGenToken;
	// home nonce index not modelled
	
	MobOption_Binding_Identifier_Mobility mobBIDmobility[];
	
}

//=============Message definition of Care-of Test Init Message ==========

packet CareOfTestInit extends MobilityHeader
{
    unsigned int careOfInitCookie;
    
    //Bruno Sousa 2010/4/30
    MobOption_Binding_Identifier_Mobility mobBIDmobility[]; 
}

//=============Message definition of Care-of Test Message ==========

packet CareOfTest extends MobilityHeader
{
    unsigned int careOfInitCookie;
    unsigned int careOfKeyGenToken;
	// care-of nonce index not modelled
	
	MobOption_Binding_Identifier_Mobility mobBIDmobility[]; 
}


///////////////////////////////////////////
// 18.09.07 - CB
///////////////////////////////////////////
packet BindingRefreshRequest extends MobilityHeader
{
    
    //Bruno Sousa 2010/4/30
    MobOption_Binding_Identifier_Mobility mobBIDmobility[]; 
}


///////////////////////////////////////////
// 17.10.07 - CB
///////////////////////////////////////////
packet HomeAddressOption extends IPv6DestinationOptionsHeader
{
    @customize(true);
    IPv6Address homeAddress;
}



