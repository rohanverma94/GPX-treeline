#include <iostream>
#include <filesystem>
#include <ctime>

#include "Config.h"
#include "tbb/parallel_reduce.h"
#include "tbb/blocked_range.h"

#include "treeline/options.h"
#include "treeline/db.h"
#include "treeline/statistics.h"
#include "treeline/status.h"
#include "treeline/record_batch.h"
#include "treeline/slice.h"
#include "treeline/pg_db.h"
#include "treeline/pg_options.h"
#include "treeline/pg_stats.h"

namespace fs = std::filesystem;

int main() {
	tl::DB *db_ = nullptr;
	tl::Options options;
	const auto dbPath = fs::path(SOURCE_DIR "/dbinstance/" + std::to_string(std::time(nullptr)));
	//init options
	options.pin_threads = false;
	options.enable_debug_log = true;
	options.key_hints.key_size = sizeof(uint64_t);
	options.key_hints.record_size = sizeof(uint64_t) * 3 + 1016;
	options.key_hints.page_fill_pct = 50;
	options.key_hints.num_keys = options.key_hints.records_per_page();

	assert(tl::DB::Open(options, dbPath, &db_).ok());
	auto key_as_int = "2122";
	const tl::Slice key(key_as_int);
	const tl::Slice value = "b21";
	std::string val;
	tl::Status st = db_->Put(tl::WriteOptions(), key, value);
	assert(st.ok());
	db_->Get(tl::ReadOptions(), key, &val);
	assert(val == value);
	std::cout << "Value for key=" << key.ToString() << " is " << val << "\n";


	//Bulk update!
	const std::vector<std::pair<const tl::Slice, const tl::Slice>> unsorted ={
			{"9",  "ello"},
			{"7", "hello"},
			{"11",  "world!"}};

	 tl::Status b = db_->BulkLoad({.sorted_load=true},(std::vector<std::pair<const tl::Slice, const tl::Slice>> &) unsorted);
	assert(b.ok());
	for(auto elem : unsorted) {
		db_->Get(tl::ReadOptions(), tl::Slice(elem.first), &val);
		std::cout << "Value for key=" << elem.first.ToString() << " is " << val << "\n";
	}
	delete (db_);
	return 0;
}
