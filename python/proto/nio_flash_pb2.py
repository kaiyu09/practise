# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: nio_flash.proto
"""Generated protocol buffer code."""
from google.protobuf.internal import builder as _builder
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\x0fnio_flash.proto\x12\tnio_flash\"\xd3\x04\n\tConfigure\x12\x13\n\x0btarget_name\x18\x01 \x01(\t\x12\x10\n\x08lib_name\x18\x02 \x01(\t\x12\x38\n\rflash_package\x18\x03 \x03(\x0b\x32!.nio_flash.Configure.FlashPackage\x1a\xd3\x02\n\x0c\x46lashPackage\x12\x0c\n\x04name\x18\x01 \x01(\t\x12\x12\n\nflash_gate\x18\x02 \x03(\t\x12\x13\n\x0bswitch_gate\x18\x03 \x03(\t\x12\x18\n\x10software_version\x18\x04 \x01(\t\x12\x18\n\x10hardware_version\x18\x05 \x01(\t\x12;\n\x0b\x62undle_type\x18\x06 \x01(\x0e\x32\x1f.nio_flash.Configure.BundleType:\x05kFull\x12\x32\n\nflash_type\x18\x07 \x01(\x0e\x32\x1e.nio_flash.Configure.FlashType\x12\x16\n\x07is_skip\x18\x08 \x01(\x08:\x05\x66\x61lse\x12\x1c\n\ris_allow_fail\x18\t \x01(\x08:\x05\x66\x61lse\x12\x31\n\tfile_list\x18\n \x03(\x0b\x32\x1e.nio_flash.Configure.FlashFile\x1a\x35\n\tFlashFile\x12\x0c\n\x04type\x18\x01 \x01(\t\x12\x0c\n\x04path\x18\x02 \x01(\t\x12\x0c\n\x04hash\x18\x03 \x01(\t\"4\n\tFlashType\x12\x08\n\x04kAll\x10\x00\x12\x0c\n\x08kSilence\x10\x01\x12\x0f\n\x0bkNonSilence\x10\x02\"\"\n\nBundleType\x12\t\n\x05kFull\x10\x00\x12\t\n\x05kDiff\x10\x01')

_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, globals())
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'nio_flash_pb2', globals())
if _descriptor._USE_C_DESCRIPTORS == False:

  DESCRIPTOR._options = None
  _CONFIGURE._serialized_start=31
  _CONFIGURE._serialized_end=626
  _CONFIGURE_FLASHPACKAGE._serialized_start=142
  _CONFIGURE_FLASHPACKAGE._serialized_end=481
  _CONFIGURE_FLASHFILE._serialized_start=483
  _CONFIGURE_FLASHFILE._serialized_end=536
  _CONFIGURE_FLASHTYPE._serialized_start=538
  _CONFIGURE_FLASHTYPE._serialized_end=590
  _CONFIGURE_BUNDLETYPE._serialized_start=592
  _CONFIGURE_BUNDLETYPE._serialized_end=626
# @@protoc_insertion_point(module_scope)
