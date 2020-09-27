////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#ifndef ACGL_RESOURCE_FILECONTROLLER_HH
#define ACGL_RESOURCE_FILECONTROLLER_HH

#include <ACGL/ACGL.hh>

#include <ACGL/Resource/BasicCreateController.hh>
#include <ACGL/Resource/BasicUpdateController.hh>
#include <ACGL/Base/FileHelpers.hh>

#include <string>

namespace ACGL{
namespace Resource{

template<typename RESOURCE>
class FileController : public BasicCreateController<RESOURCE>, public BasicUpdateController<RESOURCE>
{
    // ========================================================================================================= \/
    // ============================================================================================ CONSTRUCTORS \/
    // ========================================================================================================= \/
public:
    FileController(const std::string& _filename, const std::string& _basePath = "")
    :   mFilename(_filename),
        mFullFilePath(_basePath + _filename),
        mFileModificationTime()
    {}
    virtual ~FileController(){}

    // ==================================================================================================== \/
    // ============================================================================================ METHODS \/
    // ==================================================================================================== \/
public:
    const std::string& getFilename(void) const { return mFilename; }
    const std::string& getFullFilePath(void) const { return mFullFilePath; }

protected:
    inline bool fileIsUpToDate(void) { return Base::FileHelpers::getFileModificationTime(mFullFilePath) == mFileModificationTime; }
    inline void updateFileModificationTime(void) { mFileModificationTime = Base::FileHelpers::getFileModificationTime(mFullFilePath); }

    // =================================================================================================== \/
    // ============================================================================================ FIELDS \/
    // =================================================================================================== \/
protected:
    std::string mFilename;
    std::string mFullFilePath;

    Base::FileHelpers::FileModificationTime mFileModificationTime;
};

} // Resource
} // ACGL

#endif // ACGL_RESOURCE_BASICCONTROLLER_HH
