package main

type CreateCollectionRequest struct {
    Name      string `json:"name"`
    Dimension int    `json:"dimension"`
}

type ErrorResponse struct {
    Error string `json:"error"`
}
