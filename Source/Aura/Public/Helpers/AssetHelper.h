// Copyright, NyuAnca 2024

#pragma once

#define INIT_LOAD_ASSET(Asset, Path) \
	Asset = FSoftObjectPath { TEXT(Path) }; \
	Asset.ToSoftObjectPath().TryLoad();
