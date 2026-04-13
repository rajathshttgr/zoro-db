package services

import (
	"errors"
	"regexp"
	"strings"
	"unicode"

	"zoro/core"
)

var collectionNameRegex = regexp.MustCompile(
	`^[A-Za-z0-9](?:[A-Za-z0-9_-]*[A-Za-z0-9])?$`,
)

func CreateCollection(
	name string,
	dimension int,
	distance string,
) error {

	if dimension <= 0 || dimension > 20000 {
		return errors.New("the vector size must be between 1 and 20,000")
	}

	if name != strings.TrimSpace(name) {
		return errors.New("collection name must not contain leading or trailing spaces")
	}

	if len(name) == 0 {
		return errors.New("the collection name must not be empty")
	}

	if len(name) > 128 {
		return errors.New("the collection name must not exceed 128 characters")
	}

	if !collectionNameRegex.MatchString(name) {
		return errors.New(
			"invalid collection name: it must start and end with a letter or number, " +
			"contain only letters, numbers, '_' or '-', and include at least one letter",
		)
	}

	// no consecutive '_' or '-'
	for i := 1; i < len(name); i++ {
		if (name[i] == '_' || name[i] == '-') &&
			(name[i-1] == '_' || name[i-1] == '-') {
			return errors.New(
				"the collection name must not contain consecutive '_' or '-' characters",
			)
		}
	}

	hasLetter := false
	for _, r := range name {
		if unicode.IsLetter(r) {
			hasLetter = true
			break
		}
	}

	if !hasLetter {
		return errors.New(
			"the collection name must contain at least one letter",
		)
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


func ListCollections() ([]core.CollectionInfo, error) {
    return core.ListCollections()
}


func CheckCollectionExists(collectionName string) (bool, error){
	collectionName = strings.TrimSpace(collectionName)

	if len(collectionName) == 0 {
		return false, errors.New("invalid collection name: the collection name must not be empty")
	}
	return core.CheckCollectionExists(collectionName)
}


func GetCollectionDetails(collectionName string) (*core.CollectionInfo, error){
	return core.GetCollectionInfo(collectionName)
}