/*
 *  pixelDetector.cpp
 *  cheetah
 *
 *  Created by Anton Barty on 7/2/11.
 *  Copyright 2011 CFEL. All rights reserved.
 *
 */

//#include "release/pdsdata/cspad/ConfigV1.hh"
//#include "release/pdsdata/cspad/ConfigV2.hh"
//#include "release/pdsdata/cspad/ConfigV3.hh"
//#include "cspad/CspadTemp.hh"
//#include "cspad/CspadCorrector.hh"
//#include "cspad/CspadGeometry.hh"
#ifndef DETECTOROBJECT_H
#define DETECTOROBJECT_H

#define MAX_POWDER_CLASSES 16
#define MAX_DETECTORS 2
#define MAX_FILENAME_LENGTH 1024

/*
 * Detector geometries
 */
//	CSPAD	//
static const unsigned  CSPAD_ASIC_NX = 194;  // ASIC nx = extent of one ASIC in x
static const unsigned  CSPAD_ASIC_NY = 185;  // ASIC ny = extent of one ASIC in y
static const unsigned  CSPAD_nASICS_X = 8;   // 8 ASICs across in raw data stream
static const unsigned  CSPAD_nASICS_Y = 8;   // 8 ASICs down in raw data stresm

//	PNCCD	//
static const unsigned  PNCCD_ASIC_NX = 512;	// ASIC nx = extent of one ASIC in x
static const unsigned  PNCCD_ASIC_NY = 512;	// ASIC ny = extent of one ASIC in y
static const unsigned  PNCCD_nASICS_X = 2;		// 2 ASICs across in raw data stream
static const unsigned  PNCCD_nASICS_Y = 2;		// 2 ASICs down in raw data stresm


static const unsigned int cbufsize = 1024;

/*
 * Pixelmasks
 */


/*
 * Bits for pixel masks
 * Oriented along conventions defined for CXI file format ( https://github.com/FilipeMaia/CXI/raw/master/cxi_file_format.pdf )
 * CONVENTIONS:
 * - All options are dominantly inherited during assembly and pixel integration (see assembleImage.cpp)
 * - The default value for all options is "false"
 */
static const uint16_t PIXEL_IS_PERFECT = 0;                 // Remember to change this value if necessary after adding a new option
static const uint16_t PIXEL_IS_INVALID = 1;                 // bit 0
static const uint16_t PIXEL_IS_SATURATED = 2;               // bit 1
static const uint16_t PIXEL_IS_HOT = 4;                     // bit 2
static const uint16_t PIXEL_IS_DEAD = 8;                    // bit 3
static const uint16_t PIXEL_IS_SHADOWED = 16;               // bit 4
static const uint16_t PIXEL_IS_IN_PEAKMASK = 32;            // bit 5
static const uint16_t PIXEL_IS_TO_BE_IGNORED = 64;          // bit 6
static const uint16_t PIXEL_IS_BAD = 128;                   // bit 7
static const uint16_t PIXEL_IS_OUT_OF_RESOLUTION_LIMITS = 256; // bit 8
static const uint16_t PIXEL_IS_MISSING = 512;               // bit 9
static const uint16_t PIXEL_IS_IN_HALO = 1024;               // bit 10

// for combined options
inline bool isAnyOfBitOptionsSet(uint16_t value, uint16_t option) {return ((value & option)!=0);}
inline bool isNoneOfBitOptionsSet(uint16_t value, uint16_t option) {return ((value & option)==0);}
inline bool isAnyOfBitOptionsUnset(uint16_t value, uint16_t option) {return ((value & option)!=option);}
inline bool isNoneOfBitOptionsUnset(uint16_t value, uint16_t option) {return ((value & option)==option);}
// for single options
inline bool isBitOptionSet(uint16_t value, uint16_t option) {return isNoneOfBitOptionsUnset(value,option);}
inline bool isBitOptionUnset(uint16_t value, uint16_t option) {return isNoneOfBitOptionsSet(value,option);}


/*
 * Assemble modes (see assemble2Dimage.cpp)
 */
static const int ASSEMBLE_INTERPOLATION_LINEAR = 0; 
static const int ASSEMBLE_INTERPOLATION_NEAREST = 1; 
static const int ASSEMBLE_INTERPOLATION_DEFAULT = ASSEMBLE_INTERPOLATION_LINEAR;



#define DETECTOR_LOOP for(long detID=0; detID < global->nDetectors; detID++)

class cGlobal;


/** @brief Detector configuration common to all events */
class cPixelDetectorCommon {

public:

	/** @brief ID of grouped configuration keywords */
	char configGroup[MAX_FILENAME_LENGTH];
	/** @brief Name of the detector */
	char     detectorName[MAX_FILENAME_LENGTH];
	/** @brief Type of detector */
	char     detectorType[MAX_FILENAME_LENGTH];
	//Pds::DetInfo::Device detectorType;
    	//Pds::DetInfo::Detector detectorPdsDetInfo;

	//unsigned         configVsn;
	//unsigned         quadMask;
	//unsigned         asicMask;
	// Only required if one wants to specify front/back detector (pnccds)
	long detectorID;

	/** @brief Detector configuration file */
	char  detectorConfigFile[MAX_FILENAME_LENGTH];
	/** @brief File containing pixelmap (coordinates of pixels) */
	char  geometryFile[MAX_FILENAME_LENGTH];
	/** @brief File containing dark calibration */
	char  darkcalFile[MAX_FILENAME_LENGTH];
	/** @brief File containing gain calibration */
	char  gaincalFile[MAX_FILENAME_LENGTH];
	/** @brief File containing bad pixel mask */
	char  badpixelFile[MAX_FILENAME_LENGTH];
	/** @brief What is this? */
	char  baddataFile[MAX_FILENAME_LENGTH];
	/** @brief File containing mask of area behind wires */
	char  wireMaskFile[MAX_FILENAME_LENGTH];  // File containing mask of area behind wires


	// Detector data block size
	long  pix_nx;
	long  pix_ny;
	long  pix_nn;

	// Real space pixel locations
	float  *pix_x;
	float  *pix_y;
	float  *pix_z;

	// Reciprocal space pixel coordinates (inverse A, no factor of 2*pi)
	float  *pix_kx;
	float  *pix_ky;
	float  *pix_kz;
	float  pixelSize;

	// Assembled image size
	long  image_nx;
	long  image_nn;

	// Assembled downsampled image size
	long  imageXxX_nx;
	long  imageXxX_nn;
	long  downsampling;

	// ASIC module size
	long  asic_nx;
	long  asic_ny;
	long  asic_nn;
	long  nasics_x;
	long  nasics_y;

	// Radial averages
	float   radial_max;
	long    radial_nn;
	float   *pix_r;
	float   *pix_kr;
	float   *pix_res;

	// Polar binning
	int      radialBinSize;
	int      nRadialBins;
	int      nAngularBins;
	int     *radialBinIdx;
	int     *angularBinIdx;
	double  *polarIntensities;
	float  *pix_kphi;

	// Detector position
	char    detectorZpvname[MAX_FILENAME_LENGTH];
	float   defaultCameraLengthMm;
	float   fixedCameraLengthMm;
	float   cameraLengthOffset;
	float   cameraLengthScale;
	float   detectorZprevious;
	float   detposprev;
	double  detectorZ;
	double  detectorEncoderValue;

	// Beam center
	double  beamCenterPixX;
	double  beamCenterPixY;

	/*
	 *  Flags for detector processing options
	 */
	int    useBadPixelMask;
	int    applyBadPixelMask;
	int    useBadDataMask;
	int    useDarkcalSubtraction;
	// Subtract common mode from each ASIC
	int    cmModule;
	int    cspadSubtractUnbondedPixels;
	int    cspadSubtractBehindWires;
	float  cmFloor;    // Use lowest x% of values to estimate DC offset
	// Gain calibration
	int    useGaincal;
	int    invertGain;
	// Saturated pixels
	int    maskSaturatedPixels;
	long   pixelSaturationADC;
	// Local background subtraction
	int    useLocalBackgroundSubtraction;
	long   localBackgroundRadius;
	// Running background subtraction
	int    useSubtractPersistentBackground;
	int    subtractBg;
	int    scaleBackground;
	int    useBackgroundBufferMutex;
	float  bgMedian;
	long   bgMemory;
	long   bgRecalc;
	long   bgCounter;
	long   last_bg_update;
	int    bgIncludeHits;
	int    bgNoBeamReset;
	int    bgFiducialGlitchReset;
	// Identify persistently hot pixels
	int    useAutoHotpixel;
	int    hotpixADC;
	int    hotpixMemory;
	int    hotpixRecalc;
	float  hotpixFreq;
	long   hotpixCounter;
	long   nhot;
	long   last_hotpix_update;
	// Apply persistently hot pixels
	int    applyAutoHotpixel;
	// Identify persistently illuminated pixels (Halo)
	int    useAutoHalopixel;
	float  halopixMinDeviation;
	long    halopixRecalc;
	long    halopixMemory;
	long   halopixCounter;
	long   nhalo;
	long   last_halopix_update;
	// Start frames for calibration before output
	int    startFrames;
	// correction for PNCCD read out artifacts on back detector
	int    usePnccdOffsetCorrection;
	

	// Saving options
	int   saveDetectorCorrectedOnly;
	int   saveDetectorRaw;


	/*
	 * Arrays for all sorts of stuff
	 */
	int16_t   *bg_buffer;
	int16_t   *hotpix_buffer;
	float     *halopix_buffer;
	float     *darkcal;
	float     *selfdark;
	float     *gaincal;
	uint16_t  *pixelmask_shared;


	/*
	 * Powder patterns/sums for this detector
	 */
	FILE     *powderlogfp[MAX_POWDER_CLASSES];
	long     nPowderClasses;
	long     nPowderFrames[MAX_POWDER_CLASSES];
	double   *powderRaw[MAX_POWDER_CLASSES];
	double   *powderCorrected[MAX_POWDER_CLASSES];
	double   *powderCorrectedSquared[MAX_POWDER_CLASSES];
	double   *powderAssembled[MAX_POWDER_CLASSES];
	float   *correctedMin[MAX_POWDER_CLASSES];
	float   *assembledMin[MAX_POWDER_CLASSES];
	float   *correctedMax[MAX_POWDER_CLASSES];
	float   *assembledMax[MAX_POWDER_CLASSES];
	pthread_mutex_t powderRaw_mutex[MAX_POWDER_CLASSES];
	pthread_mutex_t powderCorrected_mutex[MAX_POWDER_CLASSES];
	pthread_mutex_t powderCorrectedSquared_mutex[MAX_POWDER_CLASSES];
	pthread_mutex_t powderAssembled_mutex[MAX_POWDER_CLASSES];
	pthread_mutex_t correctedMin_mutex[MAX_POWDER_CLASSES];
	pthread_mutex_t correctedMax_mutex[MAX_POWDER_CLASSES];
	pthread_mutex_t assembledMin_mutex[MAX_POWDER_CLASSES];
	pthread_mutex_t assembledMax_mutex[MAX_POWDER_CLASSES];

	/*
	 *  Radial stacks for this detector
	 */
	long            radialStackSize;
	long   radialStackCounter[MAX_POWDER_CLASSES];
	float   *radialAverageStack[MAX_POWDER_CLASSES];
	pthread_mutex_t radialStack_mutex[MAX_POWDER_CLASSES];



public:

	cPixelDetectorCommon();
	void configure(void);
	void parseConfigFile(char *);
	void allocatePowderMemory(cGlobal*);
	void readDetectorGeometry(char *);
	void updateKspace(cGlobal*, float);
	void readDarkcal(char *);
	void readGaincal(char *);
	void readPeakmask(cGlobal*, char *);
	void readBadpixelMask(char *);
	void readBaddataMask(char *);
	void readWireMask(char *);

//private:

	int parseConfigTag(char*, char*);

};


class cPixelDetectorEvent {

public:

	cPixelDetectorEvent();
	
	int       cspad_fail;
	uint16_t  *raw_data;
	float     *detector_corrected_data;
	float     *corrected_data;
	int16_t   *corrected_data_int16;
	uint16_t  *pixelmask;
	int16_t   *image;
	uint16_t  *image_pixelmask;
	int16_t   *imageXxX;
	uint16_t  *imageXxX_pixelmask;
	float     *radialAverage;
	float     *radialAverageCounter;
	double    detectorZ;

};

#endif