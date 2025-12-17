package services

import "zoro/api/core"

func CreateCollection(
	name string,
	dimension int,
	distance string,
) error {
	// future:
	// - validate dimension
	// - check name conflicts
	// - default configs

	return core.CreateCollection(name, dimension)
}
