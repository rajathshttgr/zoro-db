package services

import (
	"errors"
	"regexp"
	"strings"
	"unicode"

	"zoro/api/core"
)

var collectionNameRegex = regexp.MustCompile(
	`^[A-Za-z][A-Za-z0-9_-]*[A-Za-z0-9]$`,
)

func CreateCollection(
	name string,
	dimension int,
	distance string,
) error {

	if dimension <= 0 || dimension > 9999 {
		return errors.New("dimension must be between 1 and 9999")
	}

	name = strings.TrimSpace(name)

	if len(name) == 0 {
		return errors.New("collection name must not be empty")
	}

	if len(name) > 36 {
		return errors.New("collection name must be at most 36 characters long")
	}

	if !collectionNameRegex.MatchString(name) {
		return errors.New(
			`invalid collection name: must start with a letter, end with a letter or number, ` +
				`and contain only letters, numbers, '_' or '-'`,
		)
	}

	// no consecutive '_' or '-'
	for i := 1; i < len(name); i++ {
		if (name[i] == '_' || name[i] == '-') &&
			(name[i-1] == '_' || name[i-1] == '-') {
			return errors.New(
				"collection name must not contain consecutive '_' or '-' characters",
			)
		}
	}

	// must contain at least one letter or number
	hasAlnum := false
	for _, r := range name {
		if unicode.IsLetter(r) || unicode.IsDigit(r) {
			hasAlnum = true
			break
		}
	}

	if !hasAlnum {
		return errors.New(
			"collection name must contain at least one letter or number",
		)
	}

	switch distance {
	case "dot", "cosine", "l2":
		// ok
	default:
		return errors.New(`distance must be one of: "dot", "cosine", "l2"`)
	}

	return core.CreateCollection(name, dimension, distance)
}

func DeleteCollection(collectionName string) error {
	return core.DeleteCollection(collectionName)
}


func ListCollections() ([]core.CollectionInfo, error) {
    return core.ListCollections()
}

func GetCollectionInfo(collectionName string) (*core.CollectionInfo, error){
	return core.GetCollectionInfo(collectionName)
}