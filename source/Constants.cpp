// ------------------------------------------------------------------------------------------------
#include "Base/Shared.hpp"

// ------------------------------------------------------------------------------------------------
#include <limits>

// ------------------------------------------------------------------------------------------------
namespace SqMod {

/* ------------------------------------------------------------------------------------------------
 * Helper class that represents an integral enumeration value. Used to reduce compilation times.
*/
struct EnumElement
{
    CSStr Name;
    Int32 Value;
};

// ------------------------------------------------------------------------------------------------
#define SQENUMCOUNT(arr) (sizeof(arr) / sizeof(EnumElement))

// ------------------------------------------------------------------------------------------------
static const EnumElement g_ArchitectureEnum[] = {
    {_SC("Unknown"),      SQMOD_ARCH_ID_UNKNOWN},
    {_SC("X32Bit"),       SQMOD_ARCH_ID_32_BIT},
    {_SC("X64Bit"),       SQMOD_ARCH_ID_64_BIT}
};

// ------------------------------------------------------------------------------------------------
static const EnumElement g_PlatformEnum[] = {
    {_SC("Unknown"),      SQMOD_PLAT_ID_UNKNOWN},
    {_SC("Windows"),      SQMOD_PLAT_ID_WINDOWS},
    {_SC("Linux"),        SQMOD_PLAT_ID_LINUX},
    {_SC("MacOS"),        SQMOD_PLAT_ID_MACOS},
    {_SC("Unix"),         SQMOD_PLAT_ID_UNIX}
};

// ------------------------------------------------------------------------------------------------
static const EnumElement g_EventEnum[] = {
    {_SC("Unknown"),                  EVT_UNKNOWN},
    {_SC("CustomEvent"),              EVT_CUSTOMEVENT},
    {_SC("BlipCreated"),              EVT_BLIPCREATED},
    {_SC("CheckpointCreated"),        EVT_CHECKPOINTCREATED},
    {_SC("KeybindCreated"),           EVT_KEYBINDCREATED},
    {_SC("ObjectCreated"),            EVT_OBJECTCREATED},
    {_SC("PickupCreated"),            EVT_PICKUPCREATED},
    {_SC("PlayerCreated"),            EVT_PLAYERCREATED},
    {_SC("VehicleCreated"),           EVT_VEHICLECREATED},
    {_SC("BlipDestroyed"),            EVT_BLIPDESTROYED},
    {_SC("CheckpointDestroyed"),      EVT_CHECKPOINTDESTROYED},
    {_SC("KeybindDestroyed"),         EVT_KEYBINDDESTROYED},
    {_SC("ObjectDestroyed"),          EVT_OBJECTDESTROYED},
    {_SC("PickupDestroyed"),          EVT_PICKUPDESTROYED},
    {_SC("PlayerDestroyed"),          EVT_PLAYERDESTROYED},
    {_SC("VehicleDestroyed"),         EVT_VEHICLEDESTROYED},
    {_SC("BlipCustom"),               EVT_BLIPCUSTOM},
    {_SC("CheckpointCustom"),         EVT_CHECKPOINTCUSTOM},
    {_SC("KeybindCustom"),            EVT_KEYBINDCUSTOM},
    {_SC("ObjectCustom"),             EVT_OBJECTCUSTOM},
    {_SC("PickupCustom"),             EVT_PICKUPCUSTOM},
    {_SC("PlayerCustom"),             EVT_PLAYERCUSTOM},
    {_SC("VehicleCustom"),            EVT_VEHICLECUSTOM},
    {_SC("ServerStartup"),            EVT_SERVERSTARTUP},
    {_SC("ServerShutdown"),           EVT_SERVERSHUTDOWN},
    {_SC("ServerFrame"),              EVT_SERVERFRAME},
    {_SC("IncomingConnection"),       EVT_INCOMINGCONNECTION},
    {_SC("PlayerRequestClass"),       EVT_PLAYERREQUESTCLASS},
    {_SC("PlayerRequestSpawn"),       EVT_PLAYERREQUESTSPAWN},
    {_SC("PlayerSpawn"),              EVT_PLAYERSPAWN},
    {_SC("PlayerWasted"),             EVT_PLAYERWASTED},
    {_SC("PlayerKilled"),             EVT_PLAYERKILLED},
    {_SC("PlayerEmbarking"),          EVT_PLAYEREMBARKING},
    {_SC("PlayerEmbarked"),           EVT_PLAYEREMBARKED},
    {_SC("PlayerDisembark"),          EVT_PLAYERDISEMBARK},
    {_SC("PlayerRename"),             EVT_PLAYERRENAME},
    {_SC("PlayerState"),              EVT_PLAYERSTATE},
    {_SC("StateNone"),                EVT_STATENONE},
    {_SC("StateNormal"),              EVT_STATENORMAL},
    {_SC("StateAim"),                 EVT_STATEAIM},
    {_SC("StateDriver"),              EVT_STATEDRIVER},
    {_SC("StatePassenger"),           EVT_STATEPASSENGER},
    {_SC("StateEnterDriver"),         EVT_STATEENTERDRIVER},
    {_SC("StateEnterPassenger"),      EVT_STATEENTERPASSENGER},
    {_SC("StateExit"),                EVT_STATEEXIT},
    {_SC("StateUnspawned"),           EVT_STATEUNSPAWNED},
    {_SC("PlayerAction"),             EVT_PLAYERACTION},
    {_SC("ActionNone"),               EVT_ACTIONNONE},
    {_SC("ActionNormal"),             EVT_ACTIONNORMAL},
    {_SC("ActionAiming"),             EVT_ACTIONAIMING},
    {_SC("ActionShooting"),           EVT_ACTIONSHOOTING},
    {_SC("ActionJumping"),            EVT_ACTIONJUMPING},
    {_SC("ActionLieDown"),            EVT_ACTIONLIEDOWN},
    {_SC("ActionGettingUp"),          EVT_ACTIONGETTINGUP},
    {_SC("ActionJumpVehicle"),        EVT_ACTIONJUMPVEHICLE},
    {_SC("ActionDriving"),            EVT_ACTIONDRIVING},
    {_SC("ActionDying"),              EVT_ACTIONDYING},
    {_SC("ActionWasted"),             EVT_ACTIONWASTED},
    {_SC("ActionEmbarking"),          EVT_ACTIONEMBARKING},
    {_SC("ActionDisembarking"),       EVT_ACTIONDISEMBARKING},
    {_SC("PlayerBurning"),            EVT_PLAYERBURNING},
    {_SC("PlayerCrouching"),          EVT_PLAYERCROUCHING},
    {_SC("PlayerGameKeys"),           EVT_PLAYERGAMEKEYS},
    {_SC("PlayerStartTyping"),        EVT_PLAYERSTARTTYPING},
    {_SC("PlayerStopTyping"),         EVT_PLAYERSTOPTYPING},
    {_SC("PlayerAway"),               EVT_PLAYERAWAY},
    {_SC("PlayerMessage"),            EVT_PLAYERMESSAGE},
    {_SC("PlayerCommand"),            EVT_PLAYERCOMMAND},
    {_SC("PlayerPrivateMessage"),     EVT_PLAYERPRIVATEMESSAGE},
    {_SC("PlayerKeyPress"),           EVT_PLAYERKEYPRESS},
    {_SC("PlayerKeyRelease"),         EVT_PLAYERKEYRELEASE},
    {_SC("PlayerSpectate"),           EVT_PLAYERSPECTATE},
    {_SC("PlayerCrashReport"),        EVT_PLAYERCRASHREPORT},
    {_SC("VehicleExplode"),           EVT_VEHICLEEXPLODE},
    {_SC("VehicleRespawn"),           EVT_VEHICLERESPAWN},
    {_SC("ObjectShot"),               EVT_OBJECTSHOT},
    {_SC("ObjectTouched"),            EVT_OBJECTTOUCHED},
    {_SC("PickupClaimed"),            EVT_PICKUPCLAIMED},
    {_SC("PickupCollected"),          EVT_PICKUPCOLLECTED},
    {_SC("PickupRespawn"),            EVT_PICKUPRESPAWN},
    {_SC("CheckpointEntered"),        EVT_CHECKPOINTENTERED},
    {_SC("CheckpointExited"),         EVT_CHECKPOINTEXITED},
    {_SC("EntityPool"),               EVT_ENTITYPOOL},
    {_SC("ClientScriptData"),         EVT_CLIENTSCRIPTDATA},
    {_SC("PlayerUpdate"),             EVT_PLAYERUPDATE},
    {_SC("VehicleUpdate"),            EVT_VEHICLEUPDATE},
    {_SC("PlayerHealth"),             EVT_PLAYERHEALTH},
    {_SC("PlayerArmour"),             EVT_PLAYERARMOUR},
    {_SC("PlayerWeapon"),             EVT_PLAYERWEAPON},
    {_SC("PlayerHeading"),            EVT_PLAYERHEADING},
    {_SC("PlayerPosition"),           EVT_PLAYERPOSITION},
    {_SC("PlayerOption"),             EVT_PLAYEROPTION},
    {_SC("VehicleColor"),             EVT_VEHICLECOLOUR},
    {_SC("VehicleColour"),            EVT_VEHICLECOLOUR},
    {_SC("VehicleHealth"),            EVT_VEHICLEHEALTH},
    {_SC("VehiclePosition"),          EVT_VEHICLEPOSITION},
    {_SC("VehicleRotation"),          EVT_VEHICLEROTATION},
    {_SC("VehicleOption"),            EVT_VEHICLEOPTION},
    {_SC("ServerOption"),             EVT_SERVEROPTION},
    {_SC("ScriptReload"),             EVT_SCRIPTRELOAD},
    {_SC("ScriptLoaded"),             EVT_SCRIPTLOADED},
    {_SC("Max"),                      EVT_MAX}
};

// ------------------------------------------------------------------------------------------------
static const EnumElement g_CreateEnum[] = {
    {_SC("Default"),      SQMOD_CREATE_DEFAULT},
    {_SC("Manual"),       SQMOD_CREATE_MANUAL},
    {_SC("Pool"),         SQMOD_CREATE_POOL},
    {_SC("Automatic"),    SQMOD_CREATE_AUTOMATIC},
    {_SC("Overwrite"),    SQMOD_CREATE_OVERWRITE},
    {_SC("Import"),       SQMOD_CREATE_IMPORT}
};

// ------------------------------------------------------------------------------------------------
static const EnumElement g_DestroyEnum[] = {
    {_SC("Default"),      SQMOD_DESTROY_DEFAULT},
    {_SC("Manual"),       SQMOD_DESTROY_MANUAL},
    {_SC("Pool"),         SQMOD_DESTROY_POOL},
    {_SC("Automatic"),    SQMOD_DESTROY_AUTOMATIC},
    {_SC("Overwrite"),    SQMOD_DESTROY_OVERWRITE},
    {_SC("Cleanup"),      SQMOD_DESTROY_CLEANUP}
};

// ------------------------------------------------------------------------------------------------
static const EnumElement g_ServerErrorEnum[] = {
    {_SC("Unknown"),                  SQMOD_UNKNOWN},
    {_SC("None"),                     vcmpErrorNone},
    {_SC("NoSuchEntity"),             vcmpErrorNoSuchEntity},
    {_SC("BufferTooSmall"),           vcmpErrorBufferTooSmall},
    {_SC("TooLargeInput"),            vcmpErrorTooLargeInput},
    {_SC("ArgumentOutOfBounds"),      vcmpErrorArgumentOutOfBounds},
    {_SC("NullArgument"),             vcmpErrorNullArgument},
    {_SC("PoolExhausted"),            vcmpErrorPoolExhausted},
    {_SC("InvalidName"),              vcmpErrorInvalidName},
    {_SC("RequestDenied"),            vcmpErrorRequestDenied},
    {_SC("Max"),                      vcmpErrorRequestDenied}
};

// ------------------------------------------------------------------------------------------------
static const EnumElement g_EntityPoolEnum[] = {
    {_SC("Unknown"),      SQMOD_UNKNOWN},
    {_SC("Vehicle"),      vcmpEntityPoolVehicle},
    {_SC("Object"),       vcmpEntityPoolObject},
    {_SC("Pickup"),       vcmpEntityPoolPickup},
    {_SC("Radio"),        vcmpEntityPoolRadio},
    {_SC("Blip"),         vcmpEntityPoolBlip},
    {_SC("Checkpoint"),   vcmpEntityPoolCheckPoint},
    {_SC("Max"),          vcmpEntityPoolCheckPoint}
};

// ------------------------------------------------------------------------------------------------
static const EnumElement g_PlayerUpdateEnum[] = {
    {_SC("Unknown"),      SQMOD_UNKNOWN},
    {_SC("Normal"),       vcmpPlayerUpdateNormal},
    {_SC("Aiming"),       vcmpPlayerUpdateAiming},
    {_SC("Driver"),       vcmpPlayerUpdateDriver},
    {_SC("Passenger"),    vcmpPlayerUpdatePassenger},
    {_SC("Max"),          vcmpPlayerUpdatePassenger}
};

// ------------------------------------------------------------------------------------------------
static const EnumElement g_VehicleUpdateEnum[] = {
    {_SC("Unknown"),      SQMOD_UNKNOWN},
    {_SC("DriverSync"),   vcmpVehicleUpdateDriverSync},
    {_SC("OtherSync"),    vcmpVehicleUpdateOtherSync},
    {_SC("Position"),     vcmpVehicleUpdatePosition},
    {_SC("Health"),       vcmpVehicleUpdateHealth},
    {_SC("Color"),        vcmpVehicleUpdateColour},
    {_SC("Colour"),       vcmpVehicleUpdateColour},
    {_SC("Rotation"),     vcmpVehicleUpdateRotation},
    {_SC("Max"),          vcmpVehicleUpdateRotation}
};

// ------------------------------------------------------------------------------------------------
static const EnumElement g_PlayerVehicleEnum[] = {
    {_SC("Unknown"),      SQMOD_UNKNOWN},
    {_SC("Out"),          vcmpPlayerVehicleOut},
    {_SC("Entering"),     vcmpPlayerVehicleEntering},
    {_SC("Exiting"),      vcmpPlayerVehicleExiting},
    {_SC("In"),           vcmpPlayerVehicleIn},
    {_SC("Max"),          vcmpPlayerVehicleIn}
};

// ------------------------------------------------------------------------------------------------
static const EnumElement g_VehicleSyncEnum[] = {
    {_SC("Unknown"),      SQMOD_UNKNOWN},
    {_SC("None"),         vcmpVehicleSyncNone},
    {_SC("Driver"),       vcmpVehicleSyncDriver},
    {_SC("Passenger"),    vcmpVehicleSyncPassenger},
    {_SC("Near"),         vcmpVehicleSyncNear},
    {_SC("Max"),          vcmpVehicleSyncNear}
};

// ------------------------------------------------------------------------------------------------
static const EnumElement g_PartReasonEnum[] = {
    {_SC("Unknown"),      SQMOD_UNKNOWN},
    {_SC("Timeout"),      vcmpDisconnectReasonTimeout},
    {_SC("Quit"),         vcmpDisconnectReasonQuit},
    {_SC("Kick"),         vcmpDisconnectReasonKick},
    {_SC("Crash"),        vcmpDisconnectReasonCrash},
    {_SC("AntiCheat"),    vcmpDisconnectReasonAntiCheat},
    {_SC("Max"),          vcmpDisconnectReasonAntiCheat}
};

// ------------------------------------------------------------------------------------------------
static const EnumElement g_ServerOptionEnum[] = {
    {_SC("Unknown"),                  SQMOD_UNKNOWN},
    {_SC("SyncFrameLimiter"),         vcmpServerOptionSyncFrameLimiter},
    {_SC("FrameLimiter"),             vcmpServerOptionFrameLimiter},
    {_SC("TaxiBoostJump"),            vcmpServerOptionTaxiBoostJump},
    {_SC("DriveOnWater"),             vcmpServerOptionDriveOnWater},
    {_SC("FastSwitch"),               vcmpServerOptionFastSwitch},
    {_SC("FriendlyFire"),             vcmpServerOptionFriendlyFire},
    {_SC("DisableDriveBy"),           vcmpServerOptionDisableDriveBy},
    {_SC("PerfectHandling"),          vcmpServerOptionPerfectHandling},
    {_SC("FlyingCars"),               vcmpServerOptionFlyingCars},
    {_SC("JumpSwitch"),               vcmpServerOptionJumpSwitch},
    {_SC("ShowMarkers"),              vcmpServerOptionShowMarkers},
    {_SC("OnlyShowTeamMarkers"),      vcmpServerOptionOnlyShowTeamMarkers},
    {_SC("StuntBike"),                vcmpServerOptionStuntBike},
    {_SC("ShootInAir"),               vcmpServerOptionShootInAir},
    {_SC("ShowNameTags"),             vcmpServerOptionShowNameTags},
    {_SC("JoinMessages"),             vcmpServerOptionJoinMessages},
    {_SC("DeathMessages"),            vcmpServerOptionDeathMessages},
    {_SC("ChatTagsEnabled"),          vcmpServerOptionChatTagsEnabled},
    {_SC("UseClasses"),               vcmpServerOptionUseClasses},
    {_SC("WallGlitch"),               vcmpServerOptionWallGlitch},
    {_SC("DisableBackfaceCulling"),   vcmpServerOptionDisableBackfaceCulling},
    {_SC("DisableHeliBladeDamage"),   vcmpServerOptionDisableHeliBladeDamage},
    {_SC("Max"),                      vcmpServerOptionDisableHeliBladeDamage}
};

// ------------------------------------------------------------------------------------------------
static const EnumElement g_PlayerOptionEnum[] = {
    {_SC("Unknown"),          SQMOD_UNKNOWN},
    {_SC("Controllable"),     vcmpPlayerOptionControllable},
    {_SC("DriveBy"),          vcmpPlayerOptionDriveBy},
    {_SC("WhiteScanlines"),   vcmpPlayerOptionWhiteScanlines},
    {_SC("GreenScanlines"),   vcmpPlayerOptionGreenScanlines},
    {_SC("Widescreen"),       vcmpPlayerOptionWidescreen},
    {_SC("ShowMarkers"),      vcmpPlayerOptionShowMarkers},
    {_SC("CanAttack"),        vcmpPlayerOptionCanAttack},
    {_SC("HasMarker"),        vcmpPlayerOptionHasMarker},
    {_SC("ChatTagsEnabled"),  vcmpPlayerOptionChatTagsEnabled},
    {_SC("DrunkEffects"),     vcmpPlayerOptionDrunkEffects},
    {_SC("Max"),              vcmpPlayerOptionDrunkEffects}
};

// ------------------------------------------------------------------------------------------------
static const EnumElement g_VehicleOptionEnum[] = {
    {_SC("Unknown"),          SQMOD_UNKNOWN},
    {_SC("DoorsLocked"),      vcmpVehicleOptionDoorsLocked},
    {_SC("Alarm"),            vcmpVehicleOptionAlarm},
    {_SC("Lights"),           vcmpVehicleOptionLights},
    {_SC("RadioLocked"),      vcmpVehicleOptionRadioLocked},
    {_SC("Ghost"),            vcmpVehicleOptionGhost},
    {_SC("Siren"),            vcmpVehicleOptionSiren},
    {_SC("Max"),              vcmpVehicleOptionSiren}
};

// ------------------------------------------------------------------------------------------------
static const EnumElement g_BodyPartEnum[] = {
    {_SC("Unknown"),      SQMOD_UNKNOWN},
    {_SC("Body"),         vcmpBodyPartBody},
    {_SC("Torso"),        vcmpBodyPartTorso},
    {_SC("LeftArm"),      vcmpBodyPartLeftArm},
    {_SC("RightArm"),     vcmpBodyPartRightArm},
    {_SC("LeftLeg"),      vcmpBodyPartLeftLeg},
    {_SC("RightLeg"),     vcmpBodyPartRightLeg},
    {_SC("Head"),         vcmpBodyPartHead},
    {_SC("LArm"),         vcmpBodyPartLeftArm},
    {_SC("RArm"),         vcmpBodyPartRightArm},
    {_SC("LLeg"),         vcmpBodyPartLeftLeg},
    {_SC("RLeg"),         vcmpBodyPartRightLeg},
    {_SC("InVehicle"),    vcmpBodyPartInVehicle},
    {_SC("Max"),          vcmpBodyPartInVehicle}
};

// ------------------------------------------------------------------------------------------------
static const EnumElement g_PlayerStateEnum[] = {
    {_SC("Unknown"),          SQMOD_UNKNOWN},
    {_SC("None"),             vcmpPlayerStateNone},
    {_SC("Normal"),           vcmpPlayerStateNormal},
    {_SC("Aim"),              vcmpPlayerStateAim},
    {_SC("Driver"),           vcmpPlayerStateDriver},
    {_SC("Passenger"),        vcmpPlayerStatePassenger},
    {_SC("EnterDriver"),      vcmpPlayerStateEnterDriver},
    {_SC("EnterPassenger"),   vcmpPlayerStateEnterPassenger},
    {_SC("Exit"),             vcmpPlayerStateExit},
    {_SC("Unspawned"),        vcmpPlayerStateUnspawned},
    {_SC("Max"),              vcmpPlayerStateUnspawned}
};

// ------------------------------------------------------------------------------------------------
static const EnumElement g_PlayerActionEnum[] = {
    {_SC("Unknown"),              SQMOD_UNKNOWN},
    {_SC("None"),                 SQMOD_PLAYER_ACTION_NONE},
    {_SC("Normal"),               SQMOD_PLAYER_ACTION_NORMAL},
    {_SC("Aiming"),               SQMOD_PLAYER_ACTION_AIMING},
    {_SC("Shooting"),             SQMOD_PLAYER_ACTION_SHOOTING},
    {_SC("Jumping"),              SQMOD_PLAYER_ACTION_JUMPING},
    {_SC("LyingOnGround"),        SQMOD_PLAYER_ACTION_LYING_ON_GROUND},
    {_SC("GettingUp"),            SQMOD_PLAYER_ACTION_GETTING_UP},
    {_SC("JumpingFromVehicle"),   SQMOD_PLAYER_ACTION_JUMPING_FROM_VEHICLE},
    {_SC("Driving"),              SQMOD_PLAYER_ACTION_DRIVING},
    {_SC("Dying"),                SQMOD_PLAYER_ACTION_DYING},
    {_SC("Wasted"),               SQMOD_PLAYER_ACTION_WASTED},
    {_SC("EnteringVehicle"),      SQMOD_PLAYER_ACTION_ENTERING_VEHICLE},
    {_SC("ExitingVehicle"),       SQMOD_PLAYER_ACTION_EXITING_VEHICLE},
    {_SC("Max"),                  SQMOD_PLAYER_ACTION_MAX}
};

// ------------------------------------------------------------------------------------------------
static const EnumElement g_WeatherEnum[] = {
    {_SC("Unknown"),          SQMOD_UNKNOWN},
    {_SC("MostlyClear"),      SQMOD_WEATHER_MOSTLYCLEAR},
    {_SC("Overcast"),         SQMOD_WEATHER_OVERCAST},
    {_SC("ThunderStorm"),     SQMOD_WEATHER_THUNDERSTORM},
    {_SC("Storm"),            SQMOD_WEATHER_STORM},
    {_SC("Stormy"),           SQMOD_WEATHER_STORMY},
    {_SC("Foggy"),            SQMOD_WEATHER_FOGGY},
    {_SC("Fog"),              SQMOD_WEATHER_FOG},
    {_SC("Clear"),            SQMOD_WEATHER_CLEAR},
    {_SC("Sunny"),            SQMOD_WEATHER_SUNNY},
    {_SC("Rain"),             SQMOD_WEATHER_RAIN},
    {_SC("Rainy"),            SQMOD_WEATHER_RAINY},
    {_SC("DarkCloudy"),       SQMOD_WEATHER_DARKCLOUDY},
    {_SC("LightCloudy"),      SQMOD_WEATHER_LIGHTCLOUDY},
    {_SC("OvercastCloudy"),   SQMOD_WEATHER_OVERCASTCLOUDY},
    {_SC("BlackClouds"),      SQMOD_WEATHER_BLACKCLOUDS},
    {_SC("Max"),              SQMOD_WEATHER_MAX}
};

// ------------------------------------------------------------------------------------------------
static const EnumElement g_WeaponEnum[] = {
    {_SC("Unknown"),          SQMOD_UNKNOWN},
    {_SC("Unarmed"),          SQMOD_WEAPON_UNARMED},
    {_SC("BrassKnuckles"),    SQMOD_WEAPON_BRASSKNUCKLES},
    {_SC("Screwdriver"),      SQMOD_WEAPON_SCREWDRIVER},
    {_SC("GolfClub"),         SQMOD_WEAPON_GOLFCLUB},
    {_SC("Nightstick"),       SQMOD_WEAPON_NIGHTSTICK},
    {_SC("Knife"),            SQMOD_WEAPON_KNIFE},
    {_SC("BaseballBat"),      SQMOD_WEAPON_BASEBALLBAT},
    {_SC("Hammer"),           SQMOD_WEAPON_HAMMER},
    {_SC("MeatCleaver"),      SQMOD_WEAPON_MEATCLEAVER},
    {_SC("Machete"),          SQMOD_WEAPON_MACHETE},
    {_SC("Katana"),           SQMOD_WEAPON_KATANA},
    {_SC("Chainsaw"),         SQMOD_WEAPON_CHAINSAW},
    {_SC("Grenade"),          SQMOD_WEAPON_GRENADE},
    {_SC("Remote"),           SQMOD_WEAPON_REMOTE},
    {_SC("Teargas"),          SQMOD_WEAPON_TEARGAS},
    {_SC("Molotov"),          SQMOD_WEAPON_MOLOTOV},
    {_SC("Rocket"),           SQMOD_WEAPON_ROCKET},
    {_SC("Missile"),          SQMOD_WEAPON_ROCKET},
    {_SC("Colt45"),           SQMOD_WEAPON_COLT45},
    {_SC("Python"),           SQMOD_WEAPON_PYTHON},
    {_SC("Shotgun"),          SQMOD_WEAPON_SHOTGUN},
    {_SC("Spas12"),           SQMOD_WEAPON_SPAS12},
    {_SC("Stubby"),           SQMOD_WEAPON_STUBBY},
    {_SC("Tec9"),             SQMOD_WEAPON_TEC9},
    {_SC("Uzi"),              SQMOD_WEAPON_UZI},
    {_SC("Ingram"),           SQMOD_WEAPON_INGRAM},
    {_SC("MP5"),              SQMOD_WEAPON_MP5},
    {_SC("M4"),               SQMOD_WEAPON_M4},
    {_SC("Ruger"),            SQMOD_WEAPON_RUGER},
    {_SC("Sniper"),           SQMOD_WEAPON_SNIPER},
    {_SC("Laserscope"),       SQMOD_WEAPON_LASERSCOPE},
    {_SC("RocketLauncher"),   SQMOD_WEAPON_ROCKETLAUNCHER},
    {_SC("FlameThrower"),     SQMOD_WEAPON_FLAMETHROWER},
    {_SC("M60"),              SQMOD_WEAPON_M60},
    {_SC("Minigun"),          SQMOD_WEAPON_MINIGUN},
    {_SC("Bomb"),             SQMOD_WEAPON_BOMB},
    {_SC("HeliCannon"),       SQMOD_WEAPON_HELICANNON},
    {_SC("Camera"),           SQMOD_WEAPON_CAMERA},
    {_SC("Vehicle"),          SQMOD_WEAPON_VEHICLE},
    {_SC("HeliBlades1"),      SQMOD_WEAPON_HELIBLADES1},
    {_SC("Explosion1"),       SQMOD_WEAPON_EXPLOSION1},
    {_SC("Driveby"),          SQMOD_WEAPON_DRIVEBY},
    {_SC("Drowned"),          SQMOD_WEAPON_DROWNED},
    {_SC("Fall"),             SQMOD_WEAPON_FALL},
    {_SC("Explosion2"),       SQMOD_WEAPON_EXPLOSION2},
    {_SC("HeliBlades2"),      SQMOD_WEAPON_HELIBLADES2},
    {_SC("Suicide"),          SQMOD_WEAPON_SUICIDE},
    {_SC("Launcher"),         SQMOD_WEAPON_ROCKETLAUNCHER},
    {_SC("Max"),              SQMOD_WEAPON_MAX}
};

// ------------------------------------------------------------------------------------------------
static const EnumElement g_VehicleEnum[] = {
    {_SC("Unknown"),          SQMOD_UNKNOWN},
    {_SC("Landstalker"),      SQMOD_VEHICLE_LANDSTALKER},
    {_SC("Idaho"),            SQMOD_VEHICLE_IDAHO},
    {_SC("Stinger"),          SQMOD_VEHICLE_STINGER},
    {_SC("Linerunner"),       SQMOD_VEHICLE_LINERUNNER},
    {_SC("Perennial"),        SQMOD_VEHICLE_PERENNIAL},
    {_SC("Sentinel"),         SQMOD_VEHICLE_SENTINEL},
    {_SC("Rio"),              SQMOD_VEHICLE_RIO},
    {_SC("Firetruck"),        SQMOD_VEHICLE_FIRETRUCK},
    {_SC("Trashmaster"),      SQMOD_VEHICLE_TRASHMASTER},
    {_SC("Stretch"),          SQMOD_VEHICLE_STRETCH},
    {_SC("Manana"),           SQMOD_VEHICLE_MANANA},
    {_SC("Infernus"),         SQMOD_VEHICLE_INFERNUS},
    {_SC("Voodoo"),           SQMOD_VEHICLE_VOODOO},
    {_SC("Pony"),             SQMOD_VEHICLE_PONY},
    {_SC("Mule"),             SQMOD_VEHICLE_MULE},
    {_SC("Cheetah"),          SQMOD_VEHICLE_CHEETAH},
    {_SC("Ambulance"),        SQMOD_VEHICLE_AMBULANCE},
    {_SC("Fbiwashington"),    SQMOD_VEHICLE_FBIWASHINGTON},
    {_SC("Moonbeam"),         SQMOD_VEHICLE_MOONBEAM},
    {_SC("Esperanto"),        SQMOD_VEHICLE_ESPERANTO},
    {_SC("Taxi"),             SQMOD_VEHICLE_TAXI},
    {_SC("Washington"),       SQMOD_VEHICLE_WASHINGTON},
    {_SC("Bobcat"),           SQMOD_VEHICLE_BOBCAT},
    {_SC("Mrwhoopee"),        SQMOD_VEHICLE_MRWHOOPEE},
    {_SC("Bfinjection"),      SQMOD_VEHICLE_BFINJECTION},
    {_SC("Hunter"),           SQMOD_VEHICLE_HUNTER},
    {_SC("Police"),           SQMOD_VEHICLE_POLICE},
    {_SC("Enforcer"),         SQMOD_VEHICLE_ENFORCER},
    {_SC("Securicar"),        SQMOD_VEHICLE_SECURICAR},
    {_SC("Banshee"),          SQMOD_VEHICLE_BANSHEE},
    {_SC("Predator"),         SQMOD_VEHICLE_PREDATOR},
    {_SC("Bus"),              SQMOD_VEHICLE_BUS},
    {_SC("Rhino"),            SQMOD_VEHICLE_RHINO},
    {_SC("Barracksol"),       SQMOD_VEHICLE_BARRACKSOL},
    {_SC("Barracks"),         SQMOD_VEHICLE_BARRACKS},
    {_SC("Cubanhermes"),      SQMOD_VEHICLE_CUBANHERMES},
    {_SC("Helicopter"),       SQMOD_VEHICLE_HELICOPTER},
    {_SC("Angel"),            SQMOD_VEHICLE_ANGEL},
    {_SC("Coach"),            SQMOD_VEHICLE_COACH},
    {_SC("Cabbie"),           SQMOD_VEHICLE_CABBIE},
    {_SC("Stallion"),         SQMOD_VEHICLE_STALLION},
    {_SC("Rumpo"),            SQMOD_VEHICLE_RUMPO},
    {_SC("Rcbandit"),         SQMOD_VEHICLE_RCBANDIT},
    {_SC("Hearse"),           SQMOD_VEHICLE_HEARSE},
    {_SC("Packer"),           SQMOD_VEHICLE_PACKER},
    {_SC("Sentinelxs"),       SQMOD_VEHICLE_SENTINELXS},
    {_SC("Admiral"),          SQMOD_VEHICLE_ADMIRAL},
    {_SC("Squalo"),           SQMOD_VEHICLE_SQUALO},
    {_SC("Seasparrow"),       SQMOD_VEHICLE_SEASPARROW},
    {_SC("Pizzaboy"),         SQMOD_VEHICLE_PIZZABOY},
    {_SC("Gangburrito"),      SQMOD_VEHICLE_GANGBURRITO},
    {_SC("Airtrain"),         SQMOD_VEHICLE_AIRTRAIN},
    {_SC("Deaddodo"),         SQMOD_VEHICLE_DEADDODO},
    {_SC("Speeder"),          SQMOD_VEHICLE_SPEEDER},
    {_SC("Reefer"),           SQMOD_VEHICLE_REEFER},
    {_SC("Tropic"),           SQMOD_VEHICLE_TROPIC},
    {_SC("Flatbed"),          SQMOD_VEHICLE_FLATBED},
    {_SC("Yankee"),           SQMOD_VEHICLE_YANKEE},
    {_SC("Caddy"),            SQMOD_VEHICLE_CADDY},
    {_SC("Zebra"),            SQMOD_VEHICLE_ZEBRA},
    {_SC("Zebracab"),         SQMOD_VEHICLE_ZEBRACAB},
    {_SC("Topfun"),           SQMOD_VEHICLE_TOPFUN},
    {_SC("Skimmer"),          SQMOD_VEHICLE_SKIMMER},
    {_SC("Pcj600"),           SQMOD_VEHICLE_PCJ600},
    {_SC("Pcj"),              SQMOD_VEHICLE_PCJ},
    {_SC("Faggio"),           SQMOD_VEHICLE_FAGGIO},
    {_SC("Freeway"),          SQMOD_VEHICLE_FREEWAY},
    {_SC("Rcbaron"),          SQMOD_VEHICLE_RCBARON},
    {_SC("Rcraider"),         SQMOD_VEHICLE_RCRAIDER},
    {_SC("Glendale"),         SQMOD_VEHICLE_GLENDALE},
    {_SC("Oceanic"),          SQMOD_VEHICLE_OCEANIC},
    {_SC("Sanchez"),          SQMOD_VEHICLE_SANCHEZ},
    {_SC("Sparrow"),          SQMOD_VEHICLE_SPARROW},
    {_SC("Patriot"),          SQMOD_VEHICLE_PATRIOT},
    {_SC("Lovefist"),         SQMOD_VEHICLE_LOVEFIST},
    {_SC("Coastguard"),       SQMOD_VEHICLE_COASTGUARD},
    {_SC("Dinghy"),           SQMOD_VEHICLE_DINGHY},
    {_SC("Hermes"),           SQMOD_VEHICLE_HERMES},
    {_SC("Sabre"),            SQMOD_VEHICLE_SABRE},
    {_SC("Sabreturbo"),       SQMOD_VEHICLE_SABRETURBO},
    {_SC("Phoenix"),          SQMOD_VEHICLE_PHOENIX},
    {_SC("Walton"),           SQMOD_VEHICLE_WALTON},
    {_SC("Regina"),           SQMOD_VEHICLE_REGINA},
    {_SC("Comet"),            SQMOD_VEHICLE_COMET},
    {_SC("Deluxo"),           SQMOD_VEHICLE_DELUXO},
    {_SC("Burrito"),          SQMOD_VEHICLE_BURRITO},
    {_SC("Spandex"),          SQMOD_VEHICLE_SPANDEX},
    {_SC("Spandexpress"),     SQMOD_VEHICLE_SPANDEXPRESS},
    {_SC("Marquis"),          SQMOD_VEHICLE_MARQUIS},
    {_SC("Baggage"),          SQMOD_VEHICLE_BAGGAGE},
    {_SC("Baggagehandler"),   SQMOD_VEHICLE_BAGGAGEHANDLER},
    {_SC("Kaufman"),          SQMOD_VEHICLE_KAUFMAN},
    {_SC("Kaufmancab"),       SQMOD_VEHICLE_KAUFMANCAB},
    {_SC("Maverick"),         SQMOD_VEHICLE_MAVERICK},
    {_SC("Vcnmaverick"),      SQMOD_VEHICLE_VCNMAVERICK},
    {_SC("Rancher"),          SQMOD_VEHICLE_RANCHER},
    {_SC("Fbirancher"),       SQMOD_VEHICLE_FBIRANCHER},
    {_SC("Virgo"),            SQMOD_VEHICLE_VIRGO},
    {_SC("Greenwood"),        SQMOD_VEHICLE_GREENWOOD},
    {_SC("Cubanjetmax"),      SQMOD_VEHICLE_CUBANJETMAX},
    {_SC("Hotring1"),         SQMOD_VEHICLE_HOTRING1},
    {_SC("Hotringracer1"),    SQMOD_VEHICLE_HOTRINGRACER1},
    {_SC("Sandking"),         SQMOD_VEHICLE_SANDKING},
    {_SC("Blista"),           SQMOD_VEHICLE_BLISTA},
    {_SC("Blistac"),          SQMOD_VEHICLE_BLISTAC},
    {_SC("Blistacompact"),    SQMOD_VEHICLE_BLISTACOMPACT},
    {_SC("Compact"),          SQMOD_VEHICLE_COMPACT},
    {_SC("Policemav"),        SQMOD_VEHICLE_POLICEMAV},
    {_SC("Policemaverick"),   SQMOD_VEHICLE_POLICEMAVERICK},
    {_SC("Boxville"),         SQMOD_VEHICLE_BOXVILLE},
    {_SC("Benson"),           SQMOD_VEHICLE_BENSON},
    {_SC("Mesa"),             SQMOD_VEHICLE_MESA},
    {_SC("Mesagrande"),       SQMOD_VEHICLE_MESAGRANDE},
    {_SC("Rcgoblin"),         SQMOD_VEHICLE_RCGOBLIN},
    {_SC("Hotring2"),         SQMOD_VEHICLE_HOTRING2},
    {_SC("Hotringracer2"),    SQMOD_VEHICLE_HOTRINGRACER2},
    {_SC("Hotring3"),         SQMOD_VEHICLE_HOTRING3},
    {_SC("Hotringracer3"),    SQMOD_VEHICLE_HOTRINGRACER3},
    {_SC("Bloodring1"),       SQMOD_VEHICLE_BLOODRING1},
    {_SC("Bloodringbanger1"), SQMOD_VEHICLE_BLOODRINGBANGER1},
    {_SC("Bloodring2"),       SQMOD_VEHICLE_BLOODRING2},
    {_SC("Bloodringbanger2"), SQMOD_VEHICLE_BLOODRINGBANGER2},
    {_SC("Vicechee"),         SQMOD_VEHICLE_VICECHEE},
    {_SC("PoliceCheetah"),    SQMOD_VEHICLE_POLICECHEETAH},
    {_SC("FBICheetah"),       SQMOD_VEHICLE_FBICHEETAH},
    {_SC("Cheetah2"),         SQMOD_VEHICLE_CHEETAH2},
    {_SC("Max"),              SQMOD_VEHICLE_MAX}
};

// ------------------------------------------------------------------------------------------------
static const EnumElement g_SkinEnum[] = {
    {_SC("Unknown"),                SQMOD_UNKNOWN},
    {_SC("TommyVercetti"),          SQMOD_SKIN_TOMMY_VERCETTI},
    {_SC("Cop"),                    SQMOD_SKIN_COP},
    {_SC("Swat"),                   SQMOD_SKIN_SWAT},
    {_SC("FBI"),                    SQMOD_SKIN_FBI},
    {_SC("Army"),                   SQMOD_SKIN_ARMY},
    {_SC("Paramedic"),              SQMOD_SKIN_PARAMEDIC},
    {_SC("Fireman"),                SQMOD_SKIN_FIREMAN},
    {_SC("GolfGuyA"),               SQMOD_SKIN_GOLF_GUY_A},
    {_SC("BumLadyA"),               SQMOD_SKIN_BUM_LADY_A},
    {_SC("BumLadyB"),               SQMOD_SKIN_BUM_LADY_B},
    {_SC("PunkA"),                  SQMOD_SKIN_PUNK_A},
    {_SC("Lawyer"),                 SQMOD_SKIN_LAWYER},
    {_SC("SpanishLadyA"),           SQMOD_SKIN_SPANISH_LADY_A},
    {_SC("SpanishLadyB"),           SQMOD_SKIN_SPANISH_LADY_B},
    {_SC("CoolGuyA"),               SQMOD_SKIN_COOL_GUY_A},
    {_SC("ArabicGuy"),              SQMOD_SKIN_ARABIC_GUY},
    {_SC("BeachLadyA"),             SQMOD_SKIN_BEACH_LADY_A},
    {_SC("BeachLadyB"),             SQMOD_SKIN_BEACH_LADY_B},
    {_SC("BeachGuyA"),              SQMOD_SKIN_BEACH_GUY_A},
    {_SC("BeachGuyB"),              SQMOD_SKIN_BEACH_GUY_B},
    {_SC("OfficeLadyA"),            SQMOD_SKIN_OFFICE_LADY_A},
    {_SC("WaitressA"),              SQMOD_SKIN_WAITRESS_A},
    {_SC("FoodLady"),               SQMOD_SKIN_FOOD_LADY},
    {_SC("ProstituteA"),            SQMOD_SKIN_PROSTITUTE_A},
    {_SC("BumLadyC"),               SQMOD_SKIN_BUM_LADY_C},
    {_SC("BumGuyA"),                SQMOD_SKIN_BUM_GUY_A},
    {_SC("GarbageManA"),            SQMOD_SKIN_GARBAGEMAN_A},
    {_SC("TaxiDriverA"),            SQMOD_SKIN_TAXI_DRIVER_A},
    {_SC("HatianA"),                SQMOD_SKIN_HATIAN_A},
    {_SC("CriminalA"),              SQMOD_SKIN_CRIMINAL_A},
    {_SC("HoodLady"),               SQMOD_SKIN_HOOD_LADY},
    {_SC("GrannyA"),                SQMOD_SKIN_GRANNY_A},
    {_SC("BusinessManA"),           SQMOD_SKIN_BUSINESS_MAN_A},
    {_SC("ChurchGuy"),              SQMOD_SKIN_CHURCH_GUY},
    {_SC("ClubLady"),               SQMOD_SKIN_CLUB_LADY},
    {_SC("ChurchLady"),             SQMOD_SKIN_CHURCH_LADY},
    {_SC("Pimp"),                   SQMOD_SKIN_PIMP},
    {_SC("BeachLadyC"),             SQMOD_SKIN_BEACH_LADY_C},
    {_SC("BeachGuyC"),              SQMOD_SKIN_BEACH_GUY_C},
    {_SC("BeachLadyD"),             SQMOD_SKIN_BEACH_LADY_D},
    {_SC("BeachGuyD"),              SQMOD_SKIN_BEACH_GUY_D},
    {_SC("BusinessManB"),           SQMOD_SKIN_BUSINESS_MAN_B},
    {_SC("ProstituteB"),            SQMOD_SKIN_PROSTITUTE_B},
    {_SC("BumLadyD"),               SQMOD_SKIN_BUM_LADY_D},
    {_SC("BumGuyB"),                SQMOD_SKIN_BUM_GUY_B},
    {_SC("HatianB"),                SQMOD_SKIN_HATIAN_B},
    {_SC("ConstructionWorkerA"),    SQMOD_SKIN_CONSTRUCTION_WORKER_A},
    {_SC("PunkB"),                  SQMOD_SKIN_PUNK_B},
    {_SC("ProstituteC"),            SQMOD_SKIN_PROSTITUTE_C},
    {_SC("GrannyB"),                SQMOD_SKIN_GRANNY_B},
    {_SC("PunkC"),                  SQMOD_SKIN_PUNK_C},
    {_SC("BusinessManC"),           SQMOD_SKIN_BUSINESS_MAN_C},
    {_SC("SpanishLadyC"),           SQMOD_SKIN_SPANISH_LADY_C},
    {_SC("SpanishLadyD"),           SQMOD_SKIN_SPANISH_LADY_D},
    {_SC("CoolGuyB"),               SQMOD_SKIN_COOL_GUY_B},
    {_SC("BusinessManD"),           SQMOD_SKIN_BUSINESS_MAN_D},
    {_SC("BeachLadyE"),             SQMOD_SKIN_BEACH_LADY_E},
    {_SC("BeachGuyE"),              SQMOD_SKIN_BEACH_GUY_E},
    {_SC("BeachLadyF"),             SQMOD_SKIN_BEACH_LADY_F},
    {_SC("BeachGuyF"),              SQMOD_SKIN_BEACH_GUY_F},
    {_SC("ConstructionWorkerB"),    SQMOD_SKIN_CONSTRUCTION_WORKER_B},
    {_SC("GolfGuyB"),               SQMOD_SKIN_GOLF_GUY_B},
    {_SC("GolfLady"),               SQMOD_SKIN_GOLF_LADY},
    {_SC("GolfGuyC"),               SQMOD_SKIN_GOLF_GUY_C},
    {_SC("BeachLadyG"),             SQMOD_SKIN_BEACH_LADY_G},
    {_SC("BeachGuyG"),              SQMOD_SKIN_BEACH_GUY_G},
    {_SC("OfficeLadyB"),            SQMOD_SKIN_OFFICE_LADY_B},
    {_SC("BusinessManE"),           SQMOD_SKIN_BUSINESS_MAN_E},
    {_SC("BusinessManF"),           SQMOD_SKIN_BUSINESS_MAN_F},
    {_SC("ProstituteD"),            SQMOD_SKIN_PROSTITUTE_D},
    {_SC("BumLadyE"),               SQMOD_SKIN_BUM_LADY_E},
    {_SC("BumGuyC"),                SQMOD_SKIN_BUM_GUY_C},
    {_SC("SpanishGuy"),             SQMOD_SKIN_SPANISH_GUY},
    {_SC("TaxiDriverB"),            SQMOD_SKIN_TAXI_DRIVER_B},
    {_SC("GymLady"),                SQMOD_SKIN_GYM_LADY},
    {_SC("GymGuy"),                 SQMOD_SKIN_GYM_GUY},
    {_SC("SkateLady"),              SQMOD_SKIN_SKATE_LADY},
    {_SC("SkateGuy"),               SQMOD_SKIN_SKATE_GUY},
    {_SC("ShopperA"),               SQMOD_SKIN_SHOPPER_A},
    {_SC("ShopperB"),               SQMOD_SKIN_SHOPPER_B},
    {_SC("TouristA"),               SQMOD_SKIN_TOURIST_A},
    {_SC("TouristB"),               SQMOD_SKIN_TOURIST_B},
    {_SC("CubanA"),                 SQMOD_SKIN_CUBAN_A},
    {_SC("CubanB"),                 SQMOD_SKIN_CUBAN_B},
    {_SC("HatianC"),                SQMOD_SKIN_HATIAN_C},
    {_SC("HatianD"),                SQMOD_SKIN_HATIAN_D},
    {_SC("SharkA"),                 SQMOD_SKIN_SHARK_A},
    {_SC("SharkB"),                 SQMOD_SKIN_SHARK_B},
    {_SC("DiazGuyA"),               SQMOD_SKIN_DIAZ_GUY_A},
    {_SC("DiazGuyB"),               SQMOD_SKIN_DIAZ_GUY_B},
    {_SC("DBPSecurityA"),           SQMOD_SKIN_DBP_SECURITY_A},
    {_SC("DBPSecurityB"),           SQMOD_SKIN_DBP_SECURITY_B},
    {_SC("BikerA"),                 SQMOD_SKIN_BIKER_A},
    {_SC("BikerB"),                 SQMOD_SKIN_BIKER_B},
    {_SC("VercettiGuyA"),           SQMOD_SKIN_VERCETTI_GUY_A},
    {_SC("VercettiGuyB"),           SQMOD_SKIN_VERCETTI_GUY_B},
    {_SC("UndercoverCopA"),         SQMOD_SKIN_UNDERCOVER_COP_A},
    {_SC("UndercoverCopB"),         SQMOD_SKIN_UNDERCOVER_COP_B},
    {_SC("UndercoverCopC"),         SQMOD_SKIN_UNDERCOVER_COP_C},
    {_SC("UndercoverCopD"),         SQMOD_SKIN_UNDERCOVER_COP_D},
    {_SC("UndercoverCopE"),         SQMOD_SKIN_UNDERCOVER_COP_E},
    {_SC("UndercoverCopF"),         SQMOD_SKIN_UNDERCOVER_COP_F},
    {_SC("RichGuy"),                SQMOD_SKIN_RICH_GUY},
    {_SC("CoolGuyC"),               SQMOD_SKIN_COOL_GUY_C},
    {_SC("ProstituteE"),            SQMOD_SKIN_PROSTITUTE_E},
    {_SC("ProstituteF"),            SQMOD_SKIN_PROSTITUTE_F},
    {_SC("LoveFistA"),              SQMOD_SKIN_LOVE_FIST_A},
    {_SC("KenRosenburg"),           SQMOD_SKIN_KEN_ROSENBURG},
    {_SC("CandySuxx"),              SQMOD_SKIN_CANDY_SUXX},
    {_SC("Hilary"),                 SQMOD_SKIN_HILARY},
    {_SC("LoveFistB"),              SQMOD_SKIN_LOVE_FIST_B},
    {_SC("Phil"),                   SQMOD_SKIN_PHIL},
    {_SC("RockstarGuy"),            SQMOD_SKIN_ROCKSTAR_GUY},
    {_SC("Sonny"),                  SQMOD_SKIN_SONNY},
    {_SC("LanceA"),                 SQMOD_SKIN_LANCE_A},
    {_SC("MercadesA"),              SQMOD_SKIN_MERCADES_A},
    {_SC("LoveFistC"),              SQMOD_SKIN_LOVE_FIST_C},
    {_SC("AlexSrub"),               SQMOD_SKIN_ALEX_SRUB},
    {_SC("LanceCop"),               SQMOD_SKIN_LANCE_COP},
    {_SC("LanceB"),                 SQMOD_SKIN_LANCE_B},
    {_SC("Cortez"),                 SQMOD_SKIN_CORTEZ},
    {_SC("LoveFistD"),              SQMOD_SKIN_LOVE_FIST_D},
    {_SC("ColumbianGuyA"),          SQMOD_SKIN_COLUMBIAN_GUY_A},
    {_SC("HilaryRobber"),           SQMOD_SKIN_HILARY_ROBBER},
    {_SC("MercadesB"),              SQMOD_SKIN_MERCADES_B},
    {_SC("Cam"),                    SQMOD_SKIN_CAM},
    {_SC("CamRobber"),              SQMOD_SKIN_CAM_ROBBER},
    {_SC("PhilOneArm"),             SQMOD_SKIN_PHIL_ONE_ARM},
    {_SC("PhilRobber"),             SQMOD_SKIN_PHIL_ROBBER},
    {_SC("CoolGuyD"),               SQMOD_SKIN_COOL_GUY_D},
    {_SC("Pizzaman"),               SQMOD_SKIN_PIZZAMAN},
    {_SC("TaxiDriverC"),            SQMOD_SKIN_TAXI_DRIVER_C},
    {_SC("TaxiDriverD"),            SQMOD_SKIN_TAXI_DRIVER_D},
    {_SC("SailorA"),                SQMOD_SKIN_SAILOR_A},
    {_SC("SailorB"),                SQMOD_SKIN_SAILOR_B},
    {_SC("SailorC"),                SQMOD_SKIN_SAILOR_C},
    {_SC("Chef"),                   SQMOD_SKIN_CHEF},
    {_SC("CriminalB"),              SQMOD_SKIN_CRIMINAL_B},
    {_SC("FrenchGuy"),              SQMOD_SKIN_FRENCH_GUY},
    {_SC("GarbageManB"),            SQMOD_SKIN_GARBAGEMAN_B},
    {_SC("HatianE"),                SQMOD_SKIN_HATIAN_E},
    {_SC("WaitressB"),              SQMOD_SKIN_WAITRESS_B},
    {_SC("SonnyGuyA"),              SQMOD_SKIN_SONNY_GUY_A},
    {_SC("SonnyGuyB"),              SQMOD_SKIN_SONNY_GUY_B},
    {_SC("SonnyGuyC"),              SQMOD_SKIN_SONNY_GUY_C},
    {_SC("ColumbianGuyB"),          SQMOD_SKIN_COLUMBIAN_GUY_B},
    {_SC("ThugA"),                  SQMOD_SKIN_THUG_A},
    {_SC("BeachGuyH"),              SQMOD_SKIN_BEACH_GUY_H},
    {_SC("GarbageManC"),            SQMOD_SKIN_GARBAGEMAN_C},
    {_SC("GarbageManD"),            SQMOD_SKIN_GARBAGEMAN_D},
    {_SC("GarbageManE"),            SQMOD_SKIN_GARBAGEMAN_E},
    {_SC("Tranny"),                 SQMOD_SKIN_TRANNY},
    {_SC("ThugB"),                  SQMOD_SKIN_THUG_B},
    {_SC("SpandexGuyA"),            SQMOD_SKIN_SPANDEX_GUY_A},
    {_SC("SpandexGuyB"),            SQMOD_SKIN_SPANDEX_GUY_B},
    {_SC("StripperA"),              SQMOD_SKIN_STRIPPER_A},
    {_SC("StripperB"),              SQMOD_SKIN_STRIPPER_B},
    {_SC("StripperC"),              SQMOD_SKIN_STRIPPER_C},
    {_SC("StoreClerk"),             SQMOD_SKIN_STORE_CLERK},
    {_SC("Max"),                    SQMOD_SKIN_MAX}
};

// ------------------------------------------------------------------------------------------------
static const EnumElement g_KeyCodeEnum[] = {
    {_SC("Unknown"),              SQMOD_UNKNOWN},
    {_SC("Abnt_c1"),              SQMOD_KEYCODE_ABNT_C1},
    {_SC("Abnt_c2"),              SQMOD_KEYCODE_ABNT_C2},
    {_SC("Add"),                  SQMOD_KEYCODE_ADD},
    {_SC("Attn"),                 SQMOD_KEYCODE_ATTN},
    {_SC("Back"),                 SQMOD_KEYCODE_BACK},
    {_SC("Cancel"),               SQMOD_KEYCODE_CANCEL},
    {_SC("Clear"),                SQMOD_KEYCODE_CLEAR},
    {_SC("Crsel"),                SQMOD_KEYCODE_CRSEL},
    {_SC("Decimal"),              SQMOD_KEYCODE_DECIMAL},
    {_SC("Divide"),               SQMOD_KEYCODE_DIVIDE},
    {_SC("Ereof"),                SQMOD_KEYCODE_EREOF},
    {_SC("Escape"),               SQMOD_KEYCODE_ESCAPE},
    {_SC("Execute"),              SQMOD_KEYCODE_EXECUTE},
    {_SC("Exsel"),                SQMOD_KEYCODE_EXSEL},
    {_SC("Ico_clear"),            SQMOD_KEYCODE_ICO_CLEAR},
    {_SC("Ico_help"),             SQMOD_KEYCODE_ICO_HELP},
    {_SC("Key_0"),                SQMOD_KEYCODE_KEY_0},
    {_SC("Key_1"),                SQMOD_KEYCODE_KEY_1},
    {_SC("Key_2"),                SQMOD_KEYCODE_KEY_2},
    {_SC("Key_3"),                SQMOD_KEYCODE_KEY_3},
    {_SC("Key_4"),                SQMOD_KEYCODE_KEY_4},
    {_SC("Key_5"),                SQMOD_KEYCODE_KEY_5},
    {_SC("Key_6"),                SQMOD_KEYCODE_KEY_6},
    {_SC("Key_7"),                SQMOD_KEYCODE_KEY_7},
    {_SC("Key_8"),                SQMOD_KEYCODE_KEY_8},
    {_SC("Key_9"),                SQMOD_KEYCODE_KEY_9},
    {_SC("Key_a"),                SQMOD_KEYCODE_KEY_A},
    {_SC("Key_b"),                SQMOD_KEYCODE_KEY_B},
    {_SC("Key_c"),                SQMOD_KEYCODE_KEY_C},
    {_SC("Key_d"),                SQMOD_KEYCODE_KEY_D},
    {_SC("Key_e"),                SQMOD_KEYCODE_KEY_E},
    {_SC("Key_f"),                SQMOD_KEYCODE_KEY_F},
    {_SC("Key_g"),                SQMOD_KEYCODE_KEY_G},
    {_SC("Key_h"),                SQMOD_KEYCODE_KEY_H},
    {_SC("Key_i"),                SQMOD_KEYCODE_KEY_I},
    {_SC("Key_j"),                SQMOD_KEYCODE_KEY_J},
    {_SC("Key_k"),                SQMOD_KEYCODE_KEY_K},
    {_SC("Key_l"),                SQMOD_KEYCODE_KEY_L},
    {_SC("Key_m"),                SQMOD_KEYCODE_KEY_M},
    {_SC("Key_n"),                SQMOD_KEYCODE_KEY_N},
    {_SC("Key_o"),                SQMOD_KEYCODE_KEY_O},
    {_SC("Key_p"),                SQMOD_KEYCODE_KEY_P},
    {_SC("Key_q"),                SQMOD_KEYCODE_KEY_Q},
    {_SC("Key_r"),                SQMOD_KEYCODE_KEY_R},
    {_SC("Key_s"),                SQMOD_KEYCODE_KEY_S},
    {_SC("Key_t"),                SQMOD_KEYCODE_KEY_T},
    {_SC("Key_u"),                SQMOD_KEYCODE_KEY_U},
    {_SC("Key_v"),                SQMOD_KEYCODE_KEY_V},
    {_SC("Key_w"),                SQMOD_KEYCODE_KEY_W},
    {_SC("Key_x"),                SQMOD_KEYCODE_KEY_X},
    {_SC("Key_y"),                SQMOD_KEYCODE_KEY_Y},
    {_SC("Key_z"),                SQMOD_KEYCODE_KEY_Z},
    {_SC("Multiply"),             SQMOD_KEYCODE_MULTIPLY},
    {_SC("Noname"),               SQMOD_KEYCODE_NONAME},
    {_SC("Numpad0"),              SQMOD_KEYCODE_NUMPAD0},
    {_SC("Numpad1"),              SQMOD_KEYCODE_NUMPAD1},
    {_SC("Numpad2"),              SQMOD_KEYCODE_NUMPAD2},
    {_SC("Numpad3"),              SQMOD_KEYCODE_NUMPAD3},
    {_SC("Numpad4"),              SQMOD_KEYCODE_NUMPAD4},
    {_SC("Numpad5"),              SQMOD_KEYCODE_NUMPAD5},
    {_SC("Numpad6"),              SQMOD_KEYCODE_NUMPAD6},
    {_SC("Numpad7"),              SQMOD_KEYCODE_NUMPAD7},
    {_SC("Numpad8"),              SQMOD_KEYCODE_NUMPAD8},
    {_SC("Numpad9"),              SQMOD_KEYCODE_NUMPAD9},
    {_SC("Oem_1"),                SQMOD_KEYCODE_OEM_1},
    {_SC("Oem_102"),              SQMOD_KEYCODE_OEM_102},
    {_SC("Oem_2"),                SQMOD_KEYCODE_OEM_2},
    {_SC("Oem_3"),                SQMOD_KEYCODE_OEM_3},
    {_SC("Oem_4"),                SQMOD_KEYCODE_OEM_4},
    {_SC("Oem_5"),                SQMOD_KEYCODE_OEM_5},
    {_SC("Oem_6"),                SQMOD_KEYCODE_OEM_6},
    {_SC("Oem_7"),                SQMOD_KEYCODE_OEM_7},
    {_SC("Oem_8"),                SQMOD_KEYCODE_OEM_8},
    {_SC("Oem_attn"),             SQMOD_KEYCODE_OEM_ATTN},
    {_SC("Oem_auto"),             SQMOD_KEYCODE_OEM_AUTO},
    {_SC("Oem_ax"),               SQMOD_KEYCODE_OEM_AX},
    {_SC("Oem_backtab"),          SQMOD_KEYCODE_OEM_BACKTAB},
    {_SC("Oem_clear"),            SQMOD_KEYCODE_OEM_CLEAR},
    {_SC("Oem_comma"),            SQMOD_KEYCODE_OEM_COMMA},
    {_SC("Oem_copy"),             SQMOD_KEYCODE_OEM_COPY},
    {_SC("Oem_cusel"),            SQMOD_KEYCODE_OEM_CUSEL},
    {_SC("Oem_enlw"),             SQMOD_KEYCODE_OEM_ENLW},
    {_SC("Oem_finish"),           SQMOD_KEYCODE_OEM_FINISH},
    {_SC("Oem_fj_loya"),          SQMOD_KEYCODE_OEM_FJ_LOYA},
    {_SC("Oem_fj_masshou"),       SQMOD_KEYCODE_OEM_FJ_MASSHOU},
    {_SC("Oem_fj_roya"),          SQMOD_KEYCODE_OEM_FJ_ROYA},
    {_SC("Oem_fj_touroku"),       SQMOD_KEYCODE_OEM_FJ_TOUROKU},
    {_SC("Oem_jump"),             SQMOD_KEYCODE_OEM_JUMP},
    {_SC("Oem_minus"),            SQMOD_KEYCODE_OEM_MINUS},
    {_SC("Oem_pa1"),              SQMOD_KEYCODE_OEM_PA1},
    {_SC("Oem_pa2"),              SQMOD_KEYCODE_OEM_PA2},
    {_SC("Oem_pa3"),              SQMOD_KEYCODE_OEM_PA3},
    {_SC("Oem_period"),           SQMOD_KEYCODE_OEM_PERIOD},
    {_SC("Oem_plus"),             SQMOD_KEYCODE_OEM_PLUS},
    {_SC("Oem_reset"),            SQMOD_KEYCODE_OEM_RESET},
    {_SC("Oem_wsctrl"),           SQMOD_KEYCODE_OEM_WSCTRL},
    {_SC("Pa1"),                  SQMOD_KEYCODE_PA1},
    {_SC("Packet"),               SQMOD_KEYCODE_PACKET},
    {_SC("Play"),                 SQMOD_KEYCODE_PLAY},
    {_SC("Processkey"),           SQMOD_KEYCODE_PROCESSKEY},
    {_SC("Return"),               SQMOD_KEYCODE_RETURN},
    {_SC("Select"),               SQMOD_KEYCODE_SELECT},
    {_SC("Separator"),            SQMOD_KEYCODE_SEPARATOR},
    {_SC("Space"),                SQMOD_KEYCODE_SPACE},
    {_SC("Subtract"),             SQMOD_KEYCODE_SUBTRACT},
    {_SC("Tab"),                  SQMOD_KEYCODE_TAB},
    {_SC("Zoom"),                 SQMOD_KEYCODE_ZOOM},
    {_SC("Accept"),               SQMOD_KEYCODE_ACCEPT},
    {_SC("Apps"),                 SQMOD_KEYCODE_APPS},
    {_SC("Browser_back"),         SQMOD_KEYCODE_BROWSER_BACK},
    {_SC("Browser_favorites"),    SQMOD_KEYCODE_BROWSER_FAVORITES},
    {_SC("Browser_forward"),      SQMOD_KEYCODE_BROWSER_FORWARD},
    {_SC("Browser_home"),         SQMOD_KEYCODE_BROWSER_HOME},
    {_SC("Browser_refresh"),      SQMOD_KEYCODE_BROWSER_REFRESH},
    {_SC("Browser_search"),       SQMOD_KEYCODE_BROWSER_SEARCH},
    {_SC("Browser_stop"),         SQMOD_KEYCODE_BROWSER_STOP},
    {_SC("Capital"),              SQMOD_KEYCODE_CAPITAL},
    {_SC("Convert"),              SQMOD_KEYCODE_CONVERT},
    {_SC("Delete"),               SQMOD_KEYCODE_DELETE},
    {_SC("Down"),                 SQMOD_KEYCODE_DOWN},
    {_SC("End"),                  SQMOD_KEYCODE_END},
    {_SC("F1"),                   SQMOD_KEYCODE_F1},
    {_SC("F10"),                  SQMOD_KEYCODE_F10},
    {_SC("F11"),                  SQMOD_KEYCODE_F11},
    {_SC("F12"),                  SQMOD_KEYCODE_F12},
    {_SC("F13"),                  SQMOD_KEYCODE_F13},
    {_SC("F14"),                  SQMOD_KEYCODE_F14},
    {_SC("F15"),                  SQMOD_KEYCODE_F15},
    {_SC("F16"),                  SQMOD_KEYCODE_F16},
    {_SC("F17"),                  SQMOD_KEYCODE_F17},
    {_SC("F18"),                  SQMOD_KEYCODE_F18},
    {_SC("F19"),                  SQMOD_KEYCODE_F19},
    {_SC("F2"),                   SQMOD_KEYCODE_F2},
    {_SC("F20"),                  SQMOD_KEYCODE_F20},
    {_SC("F21"),                  SQMOD_KEYCODE_F21},
    {_SC("F22"),                  SQMOD_KEYCODE_F22},
    {_SC("F23"),                  SQMOD_KEYCODE_F23},
    {_SC("F24"),                  SQMOD_KEYCODE_F24},
    {_SC("F3"),                   SQMOD_KEYCODE_F3},
    {_SC("F4"),                   SQMOD_KEYCODE_F4},
    {_SC("F5"),                   SQMOD_KEYCODE_F5},
    {_SC("F6"),                   SQMOD_KEYCODE_F6},
    {_SC("F7"),                   SQMOD_KEYCODE_F7},
    {_SC("F8"),                   SQMOD_KEYCODE_F8},
    {_SC("F9"),                   SQMOD_KEYCODE_F9},
    {_SC("Final"),                SQMOD_KEYCODE_FINAL},
    {_SC("Help"),                 SQMOD_KEYCODE_HELP},
    {_SC("Home"),                 SQMOD_KEYCODE_HOME},
    {_SC("Ico_00"),               SQMOD_KEYCODE_ICO_00},
    {_SC("Insert"),               SQMOD_KEYCODE_INSERT},
    {_SC("Junja"),                SQMOD_KEYCODE_JUNJA},
    {_SC("Kana"),                 SQMOD_KEYCODE_KANA},
    {_SC("Kanji"),                SQMOD_KEYCODE_KANJI},
    {_SC("Launch_app1"),          SQMOD_KEYCODE_LAUNCH_APP1},
    {_SC("Launch_app2"),          SQMOD_KEYCODE_LAUNCH_APP2},
    {_SC("Launch_mail"),          SQMOD_KEYCODE_LAUNCH_MAIL},
    {_SC("Launch_media_select"),  SQMOD_KEYCODE_LAUNCH_MEDIA_SELECT},
    {_SC("Lbutton"),              SQMOD_KEYCODE_LBUTTON},
    {_SC("Lcontrol"),             SQMOD_KEYCODE_LCONTROL},
    {_SC("Left"),                 SQMOD_KEYCODE_LEFT},
    {_SC("Lmenu"),                SQMOD_KEYCODE_LMENU},
    {_SC("Lshift"),               SQMOD_KEYCODE_LSHIFT},
    {_SC("Lwin"),                 SQMOD_KEYCODE_LWIN},
    {_SC("Mbutton"),              SQMOD_KEYCODE_MBUTTON},
    {_SC("Media_next_track"),     SQMOD_KEYCODE_MEDIA_NEXT_TRACK},
    {_SC("Media_play_pause"),     SQMOD_KEYCODE_MEDIA_PLAY_PAUSE},
    {_SC("Media_prev_track"),     SQMOD_KEYCODE_MEDIA_PREV_TRACK},
    {_SC("Media_stop"),           SQMOD_KEYCODE_MEDIA_STOP},
    {_SC("Modechange"),           SQMOD_KEYCODE_MODECHANGE},
    {_SC("Next"),                 SQMOD_KEYCODE_NEXT},
    {_SC("Nonconvert"),           SQMOD_KEYCODE_NONCONVERT},
    {_SC("Numlock"),              SQMOD_KEYCODE_NUMLOCK},
    {_SC("Oem_fj_jisho"),         SQMOD_KEYCODE_OEM_FJ_JISHO},
    {_SC("Pause"),                SQMOD_KEYCODE_PAUSE},
    {_SC("Print"),                SQMOD_KEYCODE_PRINT},
    {_SC("Prior"),                SQMOD_KEYCODE_PRIOR},
    {_SC("Rbutton"),              SQMOD_KEYCODE_RBUTTON},
    {_SC("Rcontrol"),             SQMOD_KEYCODE_RCONTROL},
    {_SC("Right"),                SQMOD_KEYCODE_RIGHT},
    {_SC("Rmenu"),                SQMOD_KEYCODE_RMENU},
    {_SC("Rshift"),               SQMOD_KEYCODE_RSHIFT},
    {_SC("Rwin"),                 SQMOD_KEYCODE_RWIN},
    {_SC("Scroll"),               SQMOD_KEYCODE_SCROLL},
    {_SC("Sleep"),                SQMOD_KEYCODE_SLEEP},
    {_SC("Snapshot"),             SQMOD_KEYCODE_SNAPSHOT},
    {_SC("Up"),                   SQMOD_KEYCODE_UP},
    {_SC("Volume_down"),          SQMOD_KEYCODE_VOLUME_DOWN},
    {_SC("Volume_mute"),          SQMOD_KEYCODE_VOLUME_MUTE},
    {_SC("Volume_up"),            SQMOD_KEYCODE_VOLUME_UP},
    {_SC("Xbutton1"),             SQMOD_KEYCODE_XBUTTON1},
    {_SC("Xbutton2"),             SQMOD_KEYCODE_XBUTTON2},
    {_SC("None"),                 SQMOD_KEYCODE_NONE},
    {_SC("Max"),                  SQMOD_KEYCODE_MAX}
};

// ------------------------------------------------------------------------------------------------
static const EnumElement g_AsciiEnum[] = {
    {_SC("Unknown"),              SQMOD_UNKNOWN},
    {_SC("Nul"),                  SQMOD_ASCII_NUL},
    {_SC("Soh"),                  SQMOD_ASCII_SOH},
    {_SC("Stx"),                  SQMOD_ASCII_STX},
    {_SC("Etx"),                  SQMOD_ASCII_ETX},
    {_SC("Eot"),                  SQMOD_ASCII_EOT},
    {_SC("Enq"),                  SQMOD_ASCII_ENQ},
    {_SC("Ack"),                  SQMOD_ASCII_ACK},
    {_SC("Bel"),                  SQMOD_ASCII_BEL},
    {_SC("Bs"),                   SQMOD_ASCII_BS},
    {_SC("Tab"),                  SQMOD_ASCII_TAB},
    {_SC("Lf"),                   SQMOD_ASCII_LF},
    {_SC("Vt"),                   SQMOD_ASCII_VT},
    {_SC("Ff"),                   SQMOD_ASCII_FF},
    {_SC("Cr"),                   SQMOD_ASCII_CR},
    {_SC("So"),                   SQMOD_ASCII_SO},
    {_SC("Si"),                   SQMOD_ASCII_SI},
    {_SC("Dle"),                  SQMOD_ASCII_DLE},
    {_SC("Dc1"),                  SQMOD_ASCII_DC1},
    {_SC("Dc2"),                  SQMOD_ASCII_DC2},
    {_SC("Dc3"),                  SQMOD_ASCII_DC3},
    {_SC("Dc4"),                  SQMOD_ASCII_DC4},
    {_SC("Nak"),                  SQMOD_ASCII_NAK},
    {_SC("Syn"),                  SQMOD_ASCII_SYN},
    {_SC("Etb"),                  SQMOD_ASCII_ETB},
    {_SC("Can"),                  SQMOD_ASCII_CAN},
    {_SC("Em"),                   SQMOD_ASCII_EM},
    {_SC("Sub"),                  SQMOD_ASCII_SUB},
    {_SC("Esc"),                  SQMOD_ASCII_ESC},
    {_SC("Fs"),                   SQMOD_ASCII_FS},
    {_SC("Gs"),                   SQMOD_ASCII_GS},
    {_SC("Rs"),                   SQMOD_ASCII_RS},
    {_SC("Us"),                   SQMOD_ASCII_US},
    {_SC("Space"),                SQMOD_ASCII_SPACE},
    {_SC("Exclamation_point"),    SQMOD_ASCII_EXCLAMATION_POINT},
    {_SC("Double_quotes"),        SQMOD_ASCII_DOUBLE_QUOTES},
    {_SC("Number_sign"),          SQMOD_ASCII_NUMBER_SIGN},
    {_SC("Dollar_sign"),          SQMOD_ASCII_DOLLAR_SIGN},
    {_SC("Percent_sign"),         SQMOD_ASCII_PERCENT_SIGN},
    {_SC("Ampersand"),            SQMOD_ASCII_AMPERSAND},
    {_SC("Single_quote"),         SQMOD_ASCII_SINGLE_QUOTE},
    {_SC("Opening_parenthesis"),  SQMOD_ASCII_OPENING_PARENTHESIS},
    {_SC("Closing_parenthesis"),  SQMOD_ASCII_CLOSING_PARENTHESIS},
    {_SC("Asterisk"),             SQMOD_ASCII_ASTERISK},
    {_SC("Plus"),                 SQMOD_ASCII_PLUS},
    {_SC("Comma"),                SQMOD_ASCII_COMMA},
    {_SC("Minus"),                SQMOD_ASCII_MINUS},
    {_SC("Period"),               SQMOD_ASCII_PERIOD},
    {_SC("Slash"),                SQMOD_ASCII_SLASH},
    {_SC("Zero"),                 SQMOD_ASCII_ZERO},
    {_SC("One"),                  SQMOD_ASCII_ONE},
    {_SC("Two"),                  SQMOD_ASCII_TWO},
    {_SC("Three"),                SQMOD_ASCII_THREE},
    {_SC("Four"),                 SQMOD_ASCII_FOUR},
    {_SC("Five"),                 SQMOD_ASCII_FIVE},
    {_SC("Six"),                  SQMOD_ASCII_SIX},
    {_SC("Seven"),                SQMOD_ASCII_SEVEN},
    {_SC("Eight"),                SQMOD_ASCII_EIGHT},
    {_SC("Nine"),                 SQMOD_ASCII_NINE},
    {_SC("Colon"),                SQMOD_ASCII_COLON},
    {_SC("Emicolon"),             SQMOD_ASCII_EMICOLON},
    {_SC("Less_than_sign"),       SQMOD_ASCII_LESS_THAN_SIGN},
    {_SC("Equal_sign"),           SQMOD_ASCII_EQUAL_SIGN},
    {_SC("Greater_than_sign"),    SQMOD_ASCII_GREATER_THAN_SIGN},
    {_SC("Question_mark"),        SQMOD_ASCII_QUESTION_MARK},
    {_SC("At"),                   SQMOD_ASCII_AT},
    {_SC("Upper_a"),              SQMOD_ASCII_UPPER_A},
    {_SC("Upper_b"),              SQMOD_ASCII_UPPER_B},
    {_SC("Upper_c"),              SQMOD_ASCII_UPPER_C},
    {_SC("Upper_d"),              SQMOD_ASCII_UPPER_D},
    {_SC("Upper_e"),              SQMOD_ASCII_UPPER_E},
    {_SC("Upper_f"),              SQMOD_ASCII_UPPER_F},
    {_SC("Upper_g"),              SQMOD_ASCII_UPPER_G},
    {_SC("Upper_h"),              SQMOD_ASCII_UPPER_H},
    {_SC("Upper_i"),              SQMOD_ASCII_UPPER_I},
    {_SC("Upper_j"),              SQMOD_ASCII_UPPER_J},
    {_SC("Upper_k"),              SQMOD_ASCII_UPPER_K},
    {_SC("Upper_l"),              SQMOD_ASCII_UPPER_L},
    {_SC("Upper_m"),              SQMOD_ASCII_UPPER_M},
    {_SC("Upper_n"),              SQMOD_ASCII_UPPER_N},
    {_SC("Upper_o"),              SQMOD_ASCII_UPPER_O},
    {_SC("Upper_p"),              SQMOD_ASCII_UPPER_P},
    {_SC("Upper_q"),              SQMOD_ASCII_UPPER_Q},
    {_SC("Upper_r"),              SQMOD_ASCII_UPPER_R},
    {_SC("Upper_s"),              SQMOD_ASCII_UPPER_S},
    {_SC("Upper_t"),              SQMOD_ASCII_UPPER_T},
    {_SC("Upper_u"),              SQMOD_ASCII_UPPER_U},
    {_SC("Upper_v"),              SQMOD_ASCII_UPPER_V},
    {_SC("Upper_w"),              SQMOD_ASCII_UPPER_W},
    {_SC("Upper_x"),              SQMOD_ASCII_UPPER_X},
    {_SC("Upper_y"),              SQMOD_ASCII_UPPER_Y},
    {_SC("Upper_z"),              SQMOD_ASCII_UPPER_Z},
    {_SC("Opening_bracket"),      SQMOD_ASCII_OPENING_BRACKET},
    {_SC("Backslash"),            SQMOD_ASCII_BACKSLASH},
    {_SC("Closing_bracket"),      SQMOD_ASCII_CLOSING_BRACKET},
    {_SC("Caret"),                SQMOD_ASCII_CARET},
    {_SC("Underscore"),           SQMOD_ASCII_UNDERSCORE},
    {_SC("Grave_accent"),         SQMOD_ASCII_GRAVE_ACCENT},
    {_SC("Lower_a"),              SQMOD_ASCII_LOWER_A},
    {_SC("Lower_b"),              SQMOD_ASCII_LOWER_B},
    {_SC("Lower_c"),              SQMOD_ASCII_LOWER_C},
    {_SC("Lower_d"),              SQMOD_ASCII_LOWER_D},
    {_SC("Lower_e"),              SQMOD_ASCII_LOWER_E},
    {_SC("Lower_f"),              SQMOD_ASCII_LOWER_F},
    {_SC("Lower_g"),              SQMOD_ASCII_LOWER_G},
    {_SC("Lower_h"),              SQMOD_ASCII_LOWER_H},
    {_SC("Lower_i"),              SQMOD_ASCII_LOWER_I},
    {_SC("Lower_j"),              SQMOD_ASCII_LOWER_J},
    {_SC("Lower_k"),              SQMOD_ASCII_LOWER_K},
    {_SC("Lower_l"),              SQMOD_ASCII_LOWER_L},
    {_SC("Lower_m"),              SQMOD_ASCII_LOWER_M},
    {_SC("Lower_n"),              SQMOD_ASCII_LOWER_N},
    {_SC("Lower_o"),              SQMOD_ASCII_LOWER_O},
    {_SC("Lower_p"),              SQMOD_ASCII_LOWER_P},
    {_SC("Lower_q"),              SQMOD_ASCII_LOWER_Q},
    {_SC("Lower_r"),              SQMOD_ASCII_LOWER_R},
    {_SC("Lower_s"),              SQMOD_ASCII_LOWER_S},
    {_SC("Lower_t"),              SQMOD_ASCII_LOWER_T},
    {_SC("Lower_u"),              SQMOD_ASCII_LOWER_U},
    {_SC("Lower_v"),              SQMOD_ASCII_LOWER_V},
    {_SC("Lower_w"),              SQMOD_ASCII_LOWER_W},
    {_SC("Lower_x"),              SQMOD_ASCII_LOWER_X},
    {_SC("Lower_y"),              SQMOD_ASCII_LOWER_Y},
    {_SC("Lower_z"),              SQMOD_ASCII_LOWER_Z},
    {_SC("Opening_brace"),        SQMOD_ASCII_OPENING_BRACE},
    {_SC("Vertical_bar"),         SQMOD_ASCII_VERTICAL_BAR},
    {_SC("Closing_brace"),        SQMOD_ASCII_CLOSING_BRACE},
    {_SC("Tilde"),                SQMOD_ASCII_TILDE},
    {_SC("Undefined"),            SQMOD_ASCII_UNDEFINED},
    {_SC("Max"),                  SQMOD_ASCII_MAX}
};

// ------------------------------------------------------------------------------------------------
static Enumeration RegisterEnum(HSQUIRRELVM vm, CSStr name, const EnumElement * data, Uint32 count)
{
    // Allocate an empty enumeration
    Enumeration e(vm);
    // Register the values from the received data
    for (Uint32 n = 0; n < count; ++n, ++data)
    {
        e.Const(data->Name, data->Value);
    }
    // Bind the enumeration to the constant table
    ConstTable(vm).Enum(name, e);
    // Return the enumeration for further changes if necessary
    return e;
}

// ------------------------------------------------------------------------------------------------
void Register_Constants(HSQUIRRELVM vm)
{
    ConstTable(vm).Enum(_SC("SqMod"), Enumeration(vm)
        .Const(_SC("Version"),      SQMOD_VERSION)
        .Const(_SC("Success"),      SQMOD_SUCCESS)
        .Const(_SC("Failure"),      SQMOD_FAILURE)
        .Const(_SC("Unknown"),      SQMOD_UNKNOWN)
        .Const(_SC("Arch"),         SQMOD_ARCHITECTURE)
        .Const(_SC("Architecture"), SQMOD_ARCHITECTURE)
        .Const(_SC("Platform"),     SQMOD_PLATFORM)
        .Const(_SC("MinChar"),      std::numeric_limits< SQChar >::min())
        .Const(_SC("MaxChar"),      std::numeric_limits< SQChar >::max())
        .Const(_SC("MinAchar"),     std::numeric_limits< Int8 >::min())
        .Const(_SC("MaxAchar"),     std::numeric_limits< Int8 >::max())
        .Const(_SC("MinByte"),      std::numeric_limits< Uint8 >::min())
        .Const(_SC("MaxByte"),      std::numeric_limits< Uint8 >::max())
        .Const(_SC("MinShort"),     std::numeric_limits< Int16 >::min())
        .Const(_SC("MaxShort"),     std::numeric_limits< Int16 >::max())
        .Const(_SC("MinWord"),      std::numeric_limits< Uint16 >::min())
        .Const(_SC("MaxWord"),      std::numeric_limits< Uint16 >::max())
        .Const(_SC("MinInt"),       std::numeric_limits< SQInteger >::min())
        .Const(_SC("MaxInt"),       std::numeric_limits< SQInteger >::max())
        .Const(_SC("MinInteger"),   std::numeric_limits< SQInteger >::min())
        .Const(_SC("MaxInteger"),   std::numeric_limits< SQInteger >::max())
        .Const(_SC("MinInt32"),     std::numeric_limits< SQInt32 >::min())
        .Const(_SC("MaxInt32"),     std::numeric_limits< SQInt32 >::max())
        .Const(_SC("MinFloat"),     std::numeric_limits< SQFloat >::min())
        .Const(_SC("MaxFloat"),     std::numeric_limits< SQFloat >::max())
        .Const(_SC("MinFloat32"),   std::numeric_limits< Float32 >::min())
        .Const(_SC("MaxFloat32"),   std::numeric_limits< Float32 >::max())
        .Const(_SC("FpNormal"),     FP_NORMAL)
        .Const(_SC("FpSubnormal"),  FP_SUBNORMAL)
        .Const(_SC("FpZero"),       FP_ZERO)
        .Const(_SC("FpInfinite"),   FP_INFINITE)
        .Const(_SC("FpNan"),        FP_NAN)
#ifdef SQUSEDOUBLE
        .Const(_SC("HugeVal"),      HUGE_VAL)
#else
        .Const(_SC("HugeVal"),      HUGE_VALF)
#endif // SQUSEDOUBLE
        .Const(_SC("Infinity"),     static_cast< float >(INFINITY))
        .Const(_SC("Inf"),          static_cast< float >(INFINITY))
        .Const(_SC("Nan"),          static_cast< float >(NAN))
    );

    RegisterEnum(vm, _SC("SqArchitectre"),      g_ArchitectureEnum,     SQENUMCOUNT(g_ArchitectureEnum));
    RegisterEnum(vm, _SC("SqPlatform"),         g_PlatformEnum,         SQENUMCOUNT(g_PlatformEnum));
    RegisterEnum(vm, _SC("SqEvent"),            g_EventEnum,            SQENUMCOUNT(g_EventEnum));
    RegisterEnum(vm, _SC("SqCreate"),           g_CreateEnum,           SQENUMCOUNT(g_CreateEnum));
    RegisterEnum(vm, _SC("SqDestroy"),          g_DestroyEnum,          SQENUMCOUNT(g_DestroyEnum));
    RegisterEnum(vm, _SC("SqServerError"),      g_ServerErrorEnum,      SQENUMCOUNT(g_ServerErrorEnum));
    RegisterEnum(vm, _SC("SqEntityPool"),       g_EntityPoolEnum,       SQENUMCOUNT(g_EntityPoolEnum));
    RegisterEnum(vm, _SC("SqPlayerUpdate"),     g_PlayerUpdateEnum,     SQENUMCOUNT(g_PlayerUpdateEnum));
    RegisterEnum(vm, _SC("SqVehicleUpdate"),    g_VehicleUpdateEnum,    SQENUMCOUNT(g_VehicleUpdateEnum));
    RegisterEnum(vm, _SC("SqPlayerVehicle"),    g_PlayerVehicleEnum,    SQENUMCOUNT(g_PlayerVehicleEnum));
    RegisterEnum(vm, _SC("SqVehicleSync"),      g_VehicleSyncEnum,      SQENUMCOUNT(g_VehicleSyncEnum));
    RegisterEnum(vm, _SC("SqPartReason"),       g_PartReasonEnum,       SQENUMCOUNT(g_PartReasonEnum));
    RegisterEnum(vm, _SC("SqServerOption"),     g_ServerOptionEnum,     SQENUMCOUNT(g_ServerOptionEnum));
    RegisterEnum(vm, _SC("SqPlayerOption"),     g_PlayerOptionEnum,     SQENUMCOUNT(g_PlayerOptionEnum));
    RegisterEnum(vm, _SC("SqVehicleOption"),    g_VehicleOptionEnum,    SQENUMCOUNT(g_VehicleOptionEnum));
    RegisterEnum(vm, _SC("SqBodyPart"),         g_BodyPartEnum,         SQENUMCOUNT(g_BodyPartEnum));
    RegisterEnum(vm, _SC("SqPlayerState"),      g_PlayerStateEnum,      SQENUMCOUNT(g_PlayerStateEnum));
    RegisterEnum(vm, _SC("SqPlayerAction"),     g_PlayerActionEnum,     SQENUMCOUNT(g_PlayerActionEnum));
    RegisterEnum(vm, _SC("SqWeather"),          g_WeatherEnum,          SQENUMCOUNT(g_WeatherEnum));
    RegisterEnum(vm, _SC("SqWep"),              g_WeaponEnum,           SQENUMCOUNT(g_WeaponEnum));
    RegisterEnum(vm, _SC("SqVeh"),              g_VehicleEnum,          SQENUMCOUNT(g_VehicleEnum));
    RegisterEnum(vm, _SC("SqSkin"),             g_SkinEnum,             SQENUMCOUNT(g_SkinEnum));
    RegisterEnum(vm, _SC("SqKeyCode"),          g_KeyCodeEnum,          SQENUMCOUNT(g_KeyCodeEnum));
    RegisterEnum(vm, _SC("SqASCII"),            g_AsciiEnum,            SQENUMCOUNT(g_AsciiEnum));
}

} // Namespace:: SqMod
