package services

import (
	"errors"

	"zoro/api/core"
)

func UpsertPoints(
	collection_name string,
	vectors [][]float32,
	Ids []string,
	Payload []map[string]any,
) error {

	// check that vectors and Ids have same length
	if len(vectors) != len(Ids) {
		return errors.New("vectors and Ids must have the same length")
	}

	// check that Payload is either nil or has same length as vectors
	if Payload != nil && len(Payload) != len(vectors) {
		return errors.New("payload must be nil or have the same length as vectors")
	}


	// check that each vector has the same dimension
	dim := len(vectors[0])
	for _, vec := range vectors {
		if len(vec) != dim {
			return errors.New("all vectors must have the same dimension")
		}
	}

	// check collection dimension matches vector dimension 
	// replace this with caching later
	collectionInfo, err := core.GetCollectionInfo(collection_name)
	if err != nil {
		return err
	}

	if collectionInfo.Dimension != dim {
		return errors.New("vector dimension does not match collection dimension")
	}

	return core.UpsertPoints(
		collection_name,
		vectors,
		Ids,
		Payload,
	)
}