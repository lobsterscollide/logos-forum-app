{
  description = "Forum App module — coordinates UI backend with forum_comms delivery layer";

  inputs = {
    logos-module-builder.url = "github:logos-co/logos-module-builder";
    forum_comms.url = "github:lobsterscollide/logos-forum-comms";
  };

  outputs = inputs@{ logos-module-builder, ... }:
    logos-module-builder.lib.mkLogosModule {
      src = ./.;
      configFile = ./metadata.json;
      flakeInputs = inputs;
    };
}
