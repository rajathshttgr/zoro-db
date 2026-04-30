package services

import (
	"errors"
	"regexp"
	"strings"

	"zoro/core"
	"zoro/dto"
)

var collectionNameRegex = regexp.MustCompile(
	`^[A-Za-z0-9_-]{1,128}$`,
)

func isReservedName(name string) bool {
	switch name {
	case ".", "..":
		return true
	}
	return false
}

func CreateCollection(
	name string,
	dimension int,
	distance string,
) error {

	name = strings.TrimSpace(name)

	if name == "" {
		return errors.New("collection name must not be empty")
	}

	if !collectionNameRegex.MatchString(name) {
		return errors.New(
			"invalid collection name: only letters, numbers, '_' and '-' are allowed (max 128 chars)",
		)
	}

	if isReservedName(name) {
		return errors.New("invalid collection name: reserved name")
	}

	if dimension <= 0 || dimension > 20000 {
		return errors.New("vector size must be between 1 and 20,000")
	}

	switch distance {
	case "dot", "cosine", "l2":
		// ok
	default:
		return errors.New(`distance must be one of: "dot", "cosine", or "l2"`)
	}

	return core.CreateCollection(name, dimension, distance)
}

func DeleteCollection(collectionName string) error {
	return core.DeleteCollection(collectionName)
}


func ListCollections() ([]dto.CollectionInfo, error) {
    return core.ListCollections()
}


func CheckCollectionExists(collectionName string) (bool, error){
	collectionName = strings.TrimSpace(collectionName)

	if len(collectionName) == 0 {
		return false, errors.New("invalid collection name: the collection name must not be empty")
	}
	return core.CheckCollectionExists(collectionName)
}


func GetCollectionDetails(collectionName string) (*dto.CollectionInfo, error){
	return core.GetCollectionInfo(collectionName)
}