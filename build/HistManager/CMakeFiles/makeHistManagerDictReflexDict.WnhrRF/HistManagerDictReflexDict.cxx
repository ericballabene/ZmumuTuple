// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME HistManagerDictReflexDict

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "/afs/cern.ch/user/e/eballabe/public/ntuple/source/HistManager/HistManager/HistManagerDict.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static TClass *ManageHists_Dictionary();
   static void ManageHists_TClassManip(TClass*);
   static void *new_ManageHists(void *p = 0);
   static void *newArray_ManageHists(Long_t size, void *p);
   static void delete_ManageHists(void *p);
   static void deleteArray_ManageHists(void *p);
   static void destruct_ManageHists(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::ManageHists*)
   {
      ::ManageHists *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::ManageHists));
      static ::ROOT::TGenericClassInfo 
         instance("ManageHists", "ManageHists.h", 10,
                  typeid(::ManageHists), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &ManageHists_Dictionary, isa_proxy, 4,
                  sizeof(::ManageHists) );
      instance.SetNew(&new_ManageHists);
      instance.SetNewArray(&newArray_ManageHists);
      instance.SetDelete(&delete_ManageHists);
      instance.SetDeleteArray(&deleteArray_ManageHists);
      instance.SetDestructor(&destruct_ManageHists);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::ManageHists*)
   {
      return GenerateInitInstanceLocal((::ManageHists*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::ManageHists*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *ManageHists_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::ManageHists*)0x0)->GetClass();
      ManageHists_TClassManip(theClass);
   return theClass;
   }

   static void ManageHists_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *TrackHists_Dictionary();
   static void TrackHists_TClassManip(TClass*);
   static void delete_TrackHists(void *p);
   static void deleteArray_TrackHists(void *p);
   static void destruct_TrackHists(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TrackHists*)
   {
      ::TrackHists *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::TrackHists));
      static ::ROOT::TGenericClassInfo 
         instance("TrackHists", "TrackHists.h", 11,
                  typeid(::TrackHists), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &TrackHists_Dictionary, isa_proxy, 4,
                  sizeof(::TrackHists) );
      instance.SetDelete(&delete_TrackHists);
      instance.SetDeleteArray(&deleteArray_TrackHists);
      instance.SetDestructor(&destruct_TrackHists);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TrackHists*)
   {
      return GenerateInitInstanceLocal((::TrackHists*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TrackHists*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *TrackHists_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::TrackHists*)0x0)->GetClass();
      TrackHists_TClassManip(theClass);
   return theClass;
   }

   static void TrackHists_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_ManageHists(void *p) {
      return  p ? new(p) ::ManageHists : new ::ManageHists;
   }
   static void *newArray_ManageHists(Long_t nElements, void *p) {
      return p ? new(p) ::ManageHists[nElements] : new ::ManageHists[nElements];
   }
   // Wrapper around operator delete
   static void delete_ManageHists(void *p) {
      delete ((::ManageHists*)p);
   }
   static void deleteArray_ManageHists(void *p) {
      delete [] ((::ManageHists*)p);
   }
   static void destruct_ManageHists(void *p) {
      typedef ::ManageHists current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::ManageHists

namespace ROOT {
   // Wrapper around operator delete
   static void delete_TrackHists(void *p) {
      delete ((::TrackHists*)p);
   }
   static void deleteArray_TrackHists(void *p) {
      delete [] ((::TrackHists*)p);
   }
   static void destruct_TrackHists(void *p) {
      typedef ::TrackHists current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TrackHists

namespace {
  void TriggerDictionaryInitialization_libHistManagerDict_Impl() {
    static const char* headers[] = {
0    };
    static const char* includePaths[] = {
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "libHistManagerDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$HistManager/ManageHists.h")))  ManageHists;
class __attribute__((annotate("$clingAutoload$HistManager/TrackHists.h")))  TrackHists;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "libHistManagerDict dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif
#ifndef HAVE_PRETTY_FUNCTION
  #define HAVE_PRETTY_FUNCTION 1
#endif
#ifndef HAVE_64_BITS
  #define HAVE_64_BITS 1
#endif
#ifndef __IDENTIFIER_64BIT__
  #define __IDENTIFIER_64BIT__ 1
#endif
#ifndef ATLAS
  #define ATLAS 1
#endif
#ifndef ROOTCORE
  #define ROOTCORE 1
#endif
#ifndef XAOD_STANDALONE
  #define XAOD_STANDALONE 1
#endif
#ifndef XAOD_ANALYSIS
  #define XAOD_ANALYSIS 1
#endif
#ifndef ROOTCORE_RELEASE_SERIES
  #define ROOTCORE_RELEASE_SERIES 25
#endif
#ifndef PACKAGE_VERSION
  #define PACKAGE_VERSION "HistManager-00-00-00"
#endif
#ifndef PACKAGE_VERSION_UQ
  #define PACKAGE_VERSION_UQ HistManager-00-00-00
#endif
#ifndef EIGEN_DONT_VECTORIZE
  #define EIGEN_DONT_VECTORIZE 1
#endif
#ifndef USE_CMAKE
  #define USE_CMAKE 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#ifndef HISTMANAGER_HISTMANAGER_DICT_H
#define HISTMANAGER_HISTMANAGER_DICT_H

// This file includes all the header files that you need to create
// dictionaries for.

#include <HistManager/ManageHists.h>
#include <HistManager/TrackHelper.h>
#include <HistManager/TrackHists.h>

#endif


#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"ManageHists", payloadCode, "@",
"TrackHists", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("libHistManagerDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_libHistManagerDict_Impl, {{"namespace DataVector_detail { template <typename T> class DVLEltBaseInit; }", 1},{"namespace DataVector_detail { template <typename B1, typename B2, typename B3> class VirtBases; }", 1},{"template <typename T> class DataVectorBase;", 1},{"template <typename T, typename BASE> class DataVector;", 1}}, classesHeaders, /*has no C++ module*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_libHistManagerDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_libHistManagerDict() {
  TriggerDictionaryInitialization_libHistManagerDict_Impl();
}
